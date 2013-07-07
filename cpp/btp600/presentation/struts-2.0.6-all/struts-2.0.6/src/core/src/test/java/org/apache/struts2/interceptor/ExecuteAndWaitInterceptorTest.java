/*
 * $Id: ExecuteAndWaitInterceptorTest.java 476642 2006-11-18 22:40:18Z mrdon $
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
package org.apache.struts2.interceptor;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Properties;

import javax.servlet.http.HttpSession;

import org.apache.struts2.ServletActionContext;
import org.apache.struts2.StrutsTestCase;
import org.apache.struts2.views.jsp.StrutsMockHttpServletRequest;
import org.apache.struts2.views.jsp.StrutsMockHttpSession;

import com.opensymphony.xwork2.Action;
import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionProxy;
import com.opensymphony.xwork2.ActionProxyFactory;
import com.opensymphony.xwork2.DefaultActionProxyFactory;
import com.opensymphony.xwork2.ObjectFactory;
import com.opensymphony.xwork2.config.Configuration;
import com.opensymphony.xwork2.config.ConfigurationException;
import com.opensymphony.xwork2.config.ConfigurationManager;
import com.opensymphony.xwork2.config.ConfigurationProvider;
import com.opensymphony.xwork2.config.entities.ActionConfig;
import com.opensymphony.xwork2.config.entities.InterceptorMapping;
import com.opensymphony.xwork2.config.entities.PackageConfig;
import com.opensymphony.xwork2.config.entities.ResultConfig;
import com.opensymphony.xwork2.inject.ContainerBuilder;
import com.opensymphony.xwork2.interceptor.ParametersInterceptor;
import com.opensymphony.xwork2.mock.MockResult;
import com.opensymphony.xwork2.util.location.LocatableProperties;

/**
 * Test case for ExecuteAndWaitInterceptor.
 */
public class ExecuteAndWaitInterceptorTest extends StrutsTestCase {

    private StrutsMockHttpServletRequest request;
    private HttpSession httpSession;
    private Map context;
    private Map params;
    private Map session;
    private ExecuteAndWaitInterceptor waitInterceptor;

    public void _testOneWait() throws Exception {
        waitInterceptor.setDelay(0);
        waitInterceptor.setDelaySleepInterval(0);

        ActionProxy proxy = buildProxy("action1");
        String result = proxy.execute();
        assertEquals("wait", result);

        Thread.sleep(1000);

        ActionProxy proxy2 = buildProxy("action1");
        String result2 = proxy2.execute();
        assertEquals("success", result2);
    }

    public void _testTwoWait() throws Exception {
        waitInterceptor.setDelay(0);
        waitInterceptor.setDelaySleepInterval(0);

        ActionProxy proxy = buildProxy("action1");
        String result = proxy.execute();
        assertEquals("wait", result);

        Thread.sleep(300);

        ActionProxy proxy2 = buildProxy("action1");
        String result2 = proxy2.execute();
        assertEquals("wait", result2);

        Thread.sleep(300);

        ActionProxy proxy3 = buildProxy("action1");
        String result3 = proxy3.execute();
        assertEquals("success", result3);
    }

    public void _testOneWaitWithDelay() throws Exception {
        waitInterceptor.setDelay(200);
        waitInterceptor.setDelaySleepInterval(100);

        ActionProxy proxy = buildProxy("action1");
        long before = System.currentTimeMillis();
        String result = proxy.execute();
        long after = System.currentTimeMillis();
        assertEquals("wait", result);
        assertTrue("delay should be ca. 200 millis", (after - before) >= 190);

        Thread.sleep(400);

        ActionProxy proxy2 = buildProxy("action1");
        String result2 = proxy2.execute();
        assertEquals("success", result2);
    }

    public void _testTwoWaitWithDelay() throws Exception {
        waitInterceptor.setDelay(100);
        waitInterceptor.setDelaySleepInterval(100);

        ActionProxy proxy = buildProxy("action1");
        long before = System.currentTimeMillis();
        String result = proxy.execute();
        long after = System.currentTimeMillis();
        assertEquals("wait", result);
        assertTrue("delay should be ca. 100 millis", (after - before) >= 90);

        Thread.sleep(100);

        ActionProxy proxy2 = buildProxy("action1");
        long before2 = System.currentTimeMillis();
        String result2 = proxy2.execute();
        long after2 = System.currentTimeMillis();
        assertEquals("wait", result2);
        assertTrue("there should be no delay", (after2 - before2) < 110);

        Thread.sleep(400);

        ActionProxy proxy3 = buildProxy("action1");
        String result3 = proxy3.execute();
        assertEquals("success", result3);
    }

    public void testWaitDelayAndJobAlreadyDone() throws Exception {
        waitInterceptor.setDelay(1500);
        waitInterceptor.setDelaySleepInterval(100);

        ActionProxy proxy = buildProxy("action1");
        long before = System.currentTimeMillis();
        String result = proxy.execute();
        long diff = System.currentTimeMillis() - before;
        assertEquals("success", result);
        assertTrue("Job done already after 500 so there should not be such long delay", diff <= 750);
    }

    public void testWaitDelayAndJobAlreadyDone2() throws Exception {
        waitInterceptor.setDelay(1500);
        waitInterceptor.setDelaySleepInterval(200); // just takes a little longer to find out job is done

        ActionProxy proxy = buildProxy("action1");
        long before = System.currentTimeMillis();
        String result = proxy.execute();
        long diff = System.currentTimeMillis() - before;
        assertEquals("success", result);
        assertTrue("Job done already after 500 so there should not be such long delay", diff <= 750);
    }

    protected ActionProxy buildProxy(String actionName) throws Exception {
        return actionProxyFactory.createActionProxy("", actionName, context);
    }

    protected void setUp() throws Exception {
        loadConfigurationProviders(new WaitConfigurationProvider());

        session = new HashMap();
        params = new HashMap();
        context = new HashMap();
        context.put(ActionContext.SESSION, session);
        context.put(ActionContext.PARAMETERS, params);

        request = new StrutsMockHttpServletRequest();
        httpSession = new StrutsMockHttpSession();
        request.setSession(httpSession);
        request.setParameterMap(params);
        context.put(ServletActionContext.HTTP_REQUEST, request);
    }

    protected void tearDown() throws Exception {
        configurationManager.clearConfigurationProviders();
        configurationManager.destroyConfiguration();
        ActionContext.setContext(null);
    }

    private class WaitConfigurationProvider implements ConfigurationProvider {

        Configuration configuration;
        public void destroy() {
            waitInterceptor.destroy();
        }

        public boolean needsReload() {
            return false;
        }
        
        public void init(Configuration configuration) throws ConfigurationException {
            this.configuration = configuration;
        }

        public void loadPackages() throws ConfigurationException {
            PackageConfig wait = new PackageConfig("");

            Map results = new HashMap();
            results.put(Action.SUCCESS, new ResultConfig(Action.SUCCESS, MockResult.class.getName(), null));
            results.put(ExecuteAndWaitInterceptor.WAIT, new ResultConfig(ExecuteAndWaitInterceptor.WAIT, MockResult.class.getName(), null));

            // interceptors
            waitInterceptor = new ExecuteAndWaitInterceptor();
            List interceptors = new ArrayList();
            interceptors.add(new InterceptorMapping("params", new ParametersInterceptor()));
            interceptors.add(new InterceptorMapping("execAndWait", waitInterceptor));

            ActionConfig ac = new ActionConfig(null, ExecuteAndWaitDelayAction.class, null, results, interceptors);
            wait.addActionConfig("action1", ac);

            configuration.addPackageConfig("", wait);
        }

        public void register(ContainerBuilder builder, LocatableProperties props) throws ConfigurationException {
            builder.factory(ObjectFactory.class);
            builder.factory(ActionProxyFactory.class, DefaultActionProxyFactory.class);
        }

    }
}

