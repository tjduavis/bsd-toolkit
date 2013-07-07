/*
 * $Id: FilterDispatcherTest.java 484741 2006-12-08 20:22:37Z mrdon $
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
package org.apache.struts2.dispatcher;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.FilterConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts2.StrutsConstants;
import org.apache.struts2.StrutsTestCase;
import org.apache.struts2.dispatcher.mapper.ActionMapper;
import org.apache.struts2.dispatcher.mapper.ActionMapping;
import org.apache.struts2.util.ObjectFactoryDestroyable;
import org.springframework.mock.web.MockFilterConfig;
import org.springframework.mock.web.MockHttpServletRequest;
import org.springframework.mock.web.MockHttpServletResponse;
import org.springframework.mock.web.MockServletContext;

import com.mockobjects.servlet.MockFilterChain;
import com.opensymphony.xwork2.ObjectFactory;
import com.opensymphony.xwork2.config.ConfigurationManager;
import com.opensymphony.xwork2.config.impl.DefaultConfiguration;
import com.opensymphony.xwork2.inject.Container;
import com.opensymphony.xwork2.inject.ContainerBuilder;
import com.opensymphony.xwork2.inject.Context;
import com.opensymphony.xwork2.inject.Factory;

/**
 * FilterDispatcher TestCase.
 *
 * @version $Date: 2006-12-08 15:22:37 -0500 (Fri, 08 Dec 2006) $ $Id: FilterDispatcherTest.java 484741 2006-12-08 20:22:37Z mrdon $
 */
public class FilterDispatcherTest extends StrutsTestCase {


    public void testParsePackages() throws Exception {

        FilterDispatcher filterDispatcher = new FilterDispatcher();
        String[] result1 = filterDispatcher.parse("foo.bar.package1 foo.bar.package2 foo.bar.package3");
        String[] result2 = filterDispatcher.parse("foo.bar.package1\tfoo.bar.package2\tfoo.bar.package3");
        String[] result3 = filterDispatcher.parse("foo.bar.package1,foo.bar.package2,foo.bar.package3");
        String[] result4 = filterDispatcher.parse("foo.bar.package1    foo.bar.package2  \t foo.bar.package3   , foo.bar.package4");

        assertEquals(result1[0], "foo/bar/package1/");
        assertEquals(result1[1], "foo/bar/package2/");
        assertEquals(result1[2], "foo/bar/package3/");

        assertEquals(result2[0], "foo/bar/package1/");
        assertEquals(result2[1], "foo/bar/package2/");
        assertEquals(result2[2], "foo/bar/package3/");

        assertEquals(result3[0], "foo/bar/package1/");
        assertEquals(result3[1], "foo/bar/package2/");
        assertEquals(result3[2], "foo/bar/package3/");

        assertEquals(result4[0], "foo/bar/package1/");
        assertEquals(result4[1], "foo/bar/package2/");
        assertEquals(result4[2], "foo/bar/package3/");
        assertEquals(result4[3], "foo/bar/package4/");
    }

    public void testObjectFactoryDestroy() throws Exception {

        final InnerDestroyableObjectFactory destroyedObjectFactory = new InnerDestroyableObjectFactory();
        FilterDispatcher filterDispatcher = new FilterDispatcher() {
            @Override
            protected Dispatcher createDispatcher(FilterConfig cfg) {
                return new Dispatcher(cfg.getServletContext(), new HashMap()) {
                    Container cont = new ContainerBuilder()
                        .factory(ObjectFactory.class, new Factory() {
                            public Object create(Context context) throws Exception { return destroyedObjectFactory; }
                        })
                        .create(false);
                    
                    @Override
                    public Container getContainer() {
                        return cont;
                    }
                };
            }
        };
        filterDispatcher.init(new MockFilterConfig((ServletContext) null));
        
        assertFalse(destroyedObjectFactory.destroyed);
        filterDispatcher.destroy();
        assertTrue(destroyedObjectFactory.destroyed);
    }

    public void testIfActionMapperIsNullDontServiceAction() throws Exception {
        MockServletContext servletContext = new MockServletContext();
        MockFilterConfig filterConfig = new MockFilterConfig(servletContext);
        MockHttpServletRequest req = new MockHttpServletRequest(servletContext);
        MockHttpServletResponse res = new MockHttpServletResponse();
        MockFilterChain chain = new MockFilterChain();
        final NoOpDispatcher _dispatcher = new NoOpDispatcher(servletContext);
        ConfigurationManager confManager = new ConfigurationManager();
        confManager.setConfiguration(new DefaultConfiguration());
        _dispatcher.setConfigurationManager(confManager);
        Dispatcher.setInstance(_dispatcher);

        


        ObjectFactory.setObjectFactory(new InnerObjectFactory());

        FilterDispatcher filter = new FilterDispatcher() {
            protected Dispatcher createDispatcher() {
                return _dispatcher;
            }
        };
        filter.setActionMapper(null);
        filter.init(filterConfig);
        filter.doFilter(req, res, chain);

        assertFalse(_dispatcher.serviceRequest);
    }

    public void testCharacterEncodingSetBeforeRequestWrappingAndActionService() throws Exception {
        MockServletContext servletContext = new MockServletContext();
        MockFilterConfig filterConfig = new MockFilterConfig(servletContext);
        MockHttpServletRequest req = new MockHttpServletRequest(servletContext);
        MockHttpServletResponse res = new MockHttpServletResponse();
        MockFilterChain chain = new MockFilterChain();
        final InnerDispatcher _dispatcher = new InnerDispatcher(servletContext);
        Dispatcher.setInstance(null);

        DefaultConfiguration conf = new DefaultConfiguration() {
        	@Override
        	public Container getContainer() {
        		return new ContainerBuilder().create(false);
        	}
        };
       
        ConfigurationManager confManager = new ConfigurationManager();
        confManager.setConfiguration(conf);
        _dispatcher.setConfigurationManager(confManager);


        ObjectFactory.setObjectFactory(new InnerObjectFactory());

        _dispatcher.setDefaultEncoding("UTF-16_DUMMY");

        FilterDispatcher filter = new FilterDispatcher() {
            protected Dispatcher createDispatcher(FilterConfig filterConfig) {
                return _dispatcher;
            }
        };
        filter.setActionMapper(new InnerActionMapper());
        filter.init(filterConfig);
        filter.doFilter(req, res, chain);

        assertTrue(_dispatcher.wrappedRequest);
        assertTrue(_dispatcher.serviceRequest);
    }


    // === inner class ========
    public static class InnerObjectFactory extends ObjectFactory {

    }

    public static class NoOpDispatcher extends Dispatcher {
        protected boolean wrappedRequest = false;
        protected boolean serviceRequest = false;

        public NoOpDispatcher(ServletContext servletContext) {
            super(servletContext, new HashMap());
        }

        @Override
        public HttpServletRequest wrapRequest(HttpServletRequest request, ServletContext servletContext) throws IOException {
            wrappedRequest = true;
            return request;
        }

        public void serviceAction(HttpServletRequest request, HttpServletResponse response, ServletContext context, ActionMapping mapping) throws ServletException {
            serviceRequest = true;
        }
    }

    public static class InnerDispatcher extends Dispatcher {

        protected boolean wrappedRequest = false;
        protected boolean serviceRequest = false;

        public InnerDispatcher(ServletContext servletContext) {
            super(servletContext, new HashMap());
        }

        @Override
        public HttpServletRequest wrapRequest(HttpServletRequest request, ServletContext servletContext) throws IOException {
            wrappedRequest = true;
            // if we set the chracter encoding AFTER we do wrap request, we will get
            // a failing test
            assertNotNull(request.getCharacterEncoding());
            assertEquals(request.getCharacterEncoding(), "UTF-16_DUMMY");

            return request;
        }

        public void serviceAction(HttpServletRequest request, HttpServletResponse response, ServletContext context, ActionMapping mapping) throws ServletException {
            serviceRequest = true;
            // if we set the chracter encoding AFTER we do wrap request, we will get
            // a failing test
            assertNotNull(request.getCharacterEncoding());
            assertEquals(request.getCharacterEncoding(), "UTF-16_DUMMY");
        }
    }

    public static class InnerActionMapper implements ActionMapper {

        public ActionMapping getMapping(HttpServletRequest request, ConfigurationManager config) {
            return new ActionMapping();
        }

        public String getUriFromActionMapping(ActionMapping mapping) {
            return null;
        }
    }

    public static class NullActionMapper implements ActionMapper {
        public ActionMapping getMapping(HttpServletRequest request, ConfigurationManager config) {
            return null;
        }

        public String getUriFromActionMapping(ActionMapping mapping) {
            return null;
        }
    }


    public static class InnerDestroyableObjectFactory extends ObjectFactory implements ObjectFactoryDestroyable {
        public boolean destroyed = false;

        public void destroy() {
            destroyed = true;
        }
    }

}
