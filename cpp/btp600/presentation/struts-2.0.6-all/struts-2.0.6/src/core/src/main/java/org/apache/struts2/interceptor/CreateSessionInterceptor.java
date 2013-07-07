/*
 * $Id: CreateSessionInterceptor.java 471756 2006-11-06 15:01:43Z husted $
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

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts2.ServletActionContext;

import com.opensymphony.xwork2.ActionInvocation;
import com.opensymphony.xwork2.interceptor.AbstractInterceptor;

/**
 * <!-- START SNIPPET: description -->
 *
 * This interceptor creates the HttpSession.
 * <p/>
 * This is particular usefull when using the &lt;@s.token&gt; tag in freemarker templates.
 * The tag <b>do</b> require that a HttpSession is already created since freemarker commits
 * the response to the client immediately.
 *
 * <!-- END SNIPPET: description -->
 *
 * <p/> <u>Interceptor parameters:</u>
 *
 *
 * <!-- START SNIPPET: extending -->
 *
 * <ul>
 *  <li>none</li>
 * </ul>
 *
 * <!-- END SNIPPET: extending -->
 *
 *
 * <!-- START SNIPPET: parameters -->
 *
 * <ul>
 *
 * <li>None</li>
 *
 * </ul>
 *
 * <!-- END SNIPPET: parameters -->
 *
 * <b>Example:</b>
 *
 * <pre>
 * <!-- START SNIPPET: example -->
 *
 * &lt;action name="someAction" class="com.examples.SomeAction"&gt;
 *     &lt;interceptor-ref name="create-session"/&gt;
 *     &lt;interceptor-ref name="defaultStack"/&gt;
 *     &lt;result name="input"&gt;input_with_token_tag.ftl&lt;/result&gt;
 * &lt;/action&gt;
 *
 * <!-- END SNIPPET: example -->
 * </pre>
 *
 * @version $Date: 2006-11-06 10:01:43 -0500 (Mon, 06 Nov 2006) $ $Id: CreateSessionInterceptor.java 471756 2006-11-06 15:01:43Z husted $
 */
public class CreateSessionInterceptor extends AbstractInterceptor {

    private static final long serialVersionUID = -4590322556118858869L;

    private static final Log _log = LogFactory.getLog(CreateSessionInterceptor.class);


    /* (non-Javadoc)
     * @see com.opensymphony.xwork2.interceptor.Interceptor#intercept(com.opensymphony.xwork2.ActionInvocation)
     */
    public String intercept(ActionInvocation invocation) throws Exception {
        _log.debug("Creating HttpSession");
        ServletActionContext.getRequest().getSession(true);
        return invocation.invoke();
    }

}
