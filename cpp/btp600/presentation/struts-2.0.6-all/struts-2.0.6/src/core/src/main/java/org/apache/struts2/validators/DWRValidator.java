/*
 * $Id: DWRValidator.java 476642 2006-11-18 22:40:18Z mrdon $
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
package org.apache.struts2.validators;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts2.dispatcher.ApplicationMap;
import org.apache.struts2.dispatcher.Dispatcher;
import org.apache.struts2.dispatcher.RequestMap;
import org.apache.struts2.dispatcher.SessionMap;

import uk.ltd.getahead.dwr.WebContextFactory;

import com.opensymphony.xwork2.Action;
import com.opensymphony.xwork2.ActionProxy;
import com.opensymphony.xwork2.DefaultActionInvocation;
import com.opensymphony.xwork2.DefaultActionProxy;
import com.opensymphony.xwork2.ObjectFactory;
import com.opensymphony.xwork2.UnknownHandler;
import com.opensymphony.xwork2.ValidationAware;
import com.opensymphony.xwork2.ValidationAwareSupport;
import com.opensymphony.xwork2.config.Configuration;
import com.opensymphony.xwork2.config.entities.ActionConfig;

/**
 * <p/>
 * Use the dwr configuration as follows :-
 *
 * <pre>
 * <!-- START SNIPPET: dwrConfiguration -->
 *
 * &lt;dwr&lt;
 *    &lt;allow&lt;
 *      &lt;create creator="new" javascript="validator" class="org.apache.struts2.validators.DWRValidator"/&lt;
 *      &lt;convert converter="bean" match="com.opensymphony.xwork2.ValidationAwareSupport"/&lt;
 *    &lt;/allow&lt;
 * &lt;/dwr&lt;
 *
 * <!-- END SNIPPET: dwrConfiguration -->
 * </pre>
 */
public class DWRValidator {
    private static final Log LOG = LogFactory.getLog(DWRValidator.class);

    public ValidationAwareSupport doPost(String namespace, String action, Map params) throws Exception {
        HttpServletRequest req = WebContextFactory.get().getHttpServletRequest();
        ServletContext servletContext = WebContextFactory.get().getServletContext();
        HttpServletResponse res = WebContextFactory.get().getHttpServletResponse();

        Map requestParams = new HashMap(req.getParameterMap());
        if (params != null) {
            requestParams.putAll(params);
        } else {
            params = requestParams;
        }
        Map requestMap = new RequestMap(req);
        Map session = new SessionMap(req);
        Map application = new ApplicationMap(servletContext);
        Dispatcher du = Dispatcher.getInstance();
        HashMap ctx = du.createContextMap(requestMap,
                params,
                session,
                application,
                req,
                res,
                servletContext);

        try {
            Configuration cfg = du.getConfigurationManager().getConfiguration();
            ValidatorActionProxy proxy = new ValidatorActionProxy(namespace, action, ctx);
            cfg.getContainer().inject(proxy);
            proxy.prepare();
            proxy.execute();
            Object a = proxy.getAction();

            if (a instanceof ValidationAware) {
                ValidationAware aware = (ValidationAware) a;
                ValidationAwareSupport vas = new ValidationAwareSupport();
                vas.setActionErrors(aware.getActionErrors());
                vas.setActionMessages(aware.getActionMessages());
                vas.setFieldErrors(aware.getFieldErrors());

                return vas;
            } else {
                return null;
            }
        } catch (Exception e) {
            LOG.error("Error while trying to validate", e);
            return null;
        }
    }

    public static class ValidatorActionInvocation extends DefaultActionInvocation {
        private static final long serialVersionUID = -7645433725470191275L;

        protected ValidatorActionInvocation(ObjectFactory objectFactory, UnknownHandler handler, ActionProxy proxy, Map extraContext) throws Exception {
            super(objectFactory, handler, proxy, extraContext, true);
        }

        protected String invokeAction(Object action, ActionConfig actionConfig) throws Exception {
            return Action.NONE; // don't actually execute the action
        }
    }

    public static class ValidatorActionProxy extends DefaultActionProxy {
        private static final long serialVersionUID = 5754781916414047963L;

        protected ValidatorActionProxy(String namespace, String actionName, Map extraContext) throws Exception {
            super(namespace, actionName, extraContext, false, true);
        }

        public void prepare() throws Exception {
            super.prepare();
            invocation = new ValidatorActionInvocation(objectFactory, unknownHandler, this, extraContext);
        }
    }
}
