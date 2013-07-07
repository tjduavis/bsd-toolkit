/*
 * $Id: ActionComponent.java 497654 2007-01-19 00:21:57Z rgielen $
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
package org.apache.struts2.components;

import java.io.IOException;
import java.io.Writer;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts2.views.annotations.StrutsTag;
import org.apache.struts2.views.annotations.StrutsTagAttribute;
import org.apache.struts2.ServletActionContext;
import org.apache.struts2.StrutsException;
import org.apache.struts2.dispatcher.Dispatcher;
import org.apache.struts2.dispatcher.RequestMap;
import org.apache.struts2.views.jsp.TagUtils;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionProxy;
import com.opensymphony.xwork2.ActionProxyFactory;
import com.opensymphony.xwork2.inject.Inject;
import com.opensymphony.xwork2.util.ValueStack;
import com.opensymphony.xwork2.util.ValueStackFactory;

/**
 * <!-- START SNIPPET: javadoc -->
 * <p>This tag enables developers to call actions directly from a JSP page by specifying the action name and an optional
 * namespace.  The body content of the tag is used to render the results from the Action.  Any result processor defined
 * for this action in struts.xml will be ignored, <i>unless</i> the executeResult parameter is specified.</p>
 * <!-- END SNIPPET: javadoc -->
 *
 * <!-- START SNIPPET: params -->
 * <ul>
 *      <li>id (String) - the id (if specified) to put the action under stack's context.
 *      <li>name* (String) - name of the action to be executed (without the extension suffix eg. .action)</li>
 *      <li>namespace (String) - default to the namespace where this action tag is invoked</li>
 *      <li>executeResult (Boolean) -  default is false. Decides wheather the result of this action is to be executed or not</li>
 *      <li>ignoreContextParams (Boolean) - default to false. Decides wheather the request parameters are to be included when the action is invoked</li>
 * </ul>
 * <!-- END SNIPPET: params -->
 *
 * <pre>
 * <!-- START SNIPPET: javacode -->
 * public class ActionTagAction extends ActionSupport {
 *
 *  public String execute() throws Exception {
 *      return "done";
 *  }
 *
 *  public String doDefault() throws Exception {
 *      ServletActionContext.getRequest().setAttribute("stringByAction", "This is a String put in by the action's doDefault()");
 *      return "done";
 *  }
 * }
 * <!-- END SNIPPET: javacode -->
 * </pre>
 *
 * <pre>
 * <!-- START SNIPPET: strutsxml -->
 *   <xwork>
 *      ....
 *     <action name="actionTagAction1" class="tmjee.testing.ActionTagAction">
 *         <result name="done">success.jsp</result>
 *     </action>
 *      <action name="actionTagAction2" class="tmjee.testing.ActionTagAction" method="default">
 *         <result name="done">success.jsp</result>
 *     </action>
 *      ....
 *   </xwork>
 * <!-- END SNIPPET: strutsxml -->
 * </pre>
 *
 * <pre>
 * <!-- START SNIPPET: example -->
 *  <div>The following action tag will execute result and include it in this page</div>
 *  <br />
 *  <s:action name="actionTagAction" executeResult="true" />
 *  <br />
 *  <div>The following action tag will do the same as above, but invokes method specialMethod in action</div>
 *  <br />
 *  <s:action name="actionTagAction!specialMethod" executeResult="true" />
 *  <br />
 *  <div>The following action tag will not execute result, but put a String in request scope
 *       under an id "stringByAction" which will be retrieved using property tag</div>
 *  <s:action name="actionTagAction!default" executeResult="false" />
 *  <s:property value="#attr.stringByAction" />
 * <!-- END SNIPPET: example -->
 * </pre>
 *
 */
@StrutsTag(name="action", tldTagClass="org.apache.struts2.views.jsp.ActionTag", description="Execute an action from within a view")
public class ActionComponent extends Component {
    private static final Log LOG = LogFactory.getLog(ActionComponent.class);

    protected HttpServletResponse res;
    protected HttpServletRequest req;

    protected ActionProxyFactory actionProxyFactory;
    protected ActionProxy proxy;
    protected String name;
    protected String namespace;
    protected boolean executeResult;
    protected boolean ignoreContextParams;
    protected boolean flush = true;

    public ActionComponent(ValueStack stack, HttpServletRequest req, HttpServletResponse res) {
        super(stack);
        this.req = req;
        this.res = res;
    }

    /**
     * @param actionProxyFactory the actionProxyFactory to set
     */
    @Inject
    public void setActionProxyFactory(ActionProxyFactory actionProxyFactory) {
        this.actionProxyFactory = actionProxyFactory;
    }

    public boolean end(Writer writer, String body) {
        boolean end = super.end(writer, "", false);
        try {
            if (flush) {
                try {
                    writer.flush();
                } catch (IOException e) {
                    LOG.warn("error while trying to flush writer ", e);
                }
            }
            executeAction();

            if ((getId() != null) && (proxy != null)) {
                getStack().setValue("#attr['" + getId() + "']",
                        proxy.getAction());
            }
        } finally {
            popComponentStack();
        }
        return end;
    }

    private Map createExtraContext() {
        Map parentParams = null;

        if (!ignoreContextParams) {
            parentParams = new ActionContext(getStack().getContext()).getParameters();
        }

        Map newParams = (parentParams != null) ? new HashMap(parentParams) : new HashMap();

        if (parameters != null) {
            newParams.putAll(parameters);
        }

        ActionContext ctx = new ActionContext(stack.getContext());
        ServletContext servletContext = (ServletContext) ctx.get(ServletActionContext.SERVLET_CONTEXT);
        PageContext pageContext = (PageContext) ctx.get(ServletActionContext.PAGE_CONTEXT);
        Map session = ctx.getSession();
        Map application = ctx.getApplication();

        Dispatcher du = Dispatcher.getInstance();
        Map extraContext = du.createContextMap(new RequestMap(req),
                newParams,
                session,
                application,
                req,
                res,
                servletContext);

        ValueStack newStack = ValueStackFactory.getFactory().createValueStack(stack);
        extraContext.put(ActionContext.VALUE_STACK, newStack);

        // add page context, such that ServletDispatcherResult will do an include
        extraContext.put(ServletActionContext.PAGE_CONTEXT, pageContext);

        return extraContext;
    }

    public ActionProxy getProxy() {
        return proxy;
    }

    /**
     * Execute the requested action.  If no namespace is provided, we'll
     * attempt to derive a namespace using buildNamespace().  The ActionProxy
     * and the namespace will be saved into the instance variables proxy and
     * namespace respectively.
     *
     * @see org.apache.struts2.views.jsp.TagUtils#buildNamespace
     */
    private void executeAction() {
        String actualName = findString(name, "name", "Action name is required. Example: updatePerson");

        if (actualName == null) {
            throw new StrutsException("Unable to find value for name " + name);
        }

        // handle "name!method" convention.
        final String actionName;
        final String methodName;

        int exclamation = actualName.lastIndexOf("!");
        if (exclamation != -1) {
            actionName = actualName.substring(0, exclamation);
            methodName = actualName.substring(exclamation + 1);
        } else {
            actionName = actualName;
            methodName = null;
        }

        String namespace;

        if (this.namespace == null) {
            namespace = TagUtils.buildNamespace(actionMapper, getStack(), req);
        } else {
            namespace = findString(this.namespace);
        }

        // get the old value stack from the request
        ValueStack stack = getStack();
        // execute at this point, after params have been set
        try {

            proxy = actionProxyFactory.createActionProxy(namespace, actionName, createExtraContext(), executeResult, true);
            if (null != methodName) {
                proxy.setMethod(methodName);
            }
            // set the new stack into the request for the taglib to use
            req.setAttribute(ServletActionContext.STRUTS_VALUESTACK_KEY, proxy.getInvocation().getStack());
            proxy.execute();

        } catch (Exception e) {
            String message = "Could not execute action: " + namespace + "/" + actualName;
            LOG.error(message, e);
        } finally {
            // set the old stack back on the request
            req.setAttribute(ServletActionContext.STRUTS_VALUESTACK_KEY, stack);
        }

        if ((getId() != null) && (proxy != null)) {
            final Map context = stack.getContext();
            context.put(getId(), proxy.getAction());
        }
    }

    @StrutsTagAttribute(required=true,description="Name of the action to be executed (without the extension suffix eg. .action)")
    public void setName(String name) {
        this.name = name;
    }

    @StrutsTagAttribute(description="Namespace for action to call", defaultValue="namespace from where tag is used")
    public void setNamespace(String namespace) {
        this.namespace = namespace;
    }

    @StrutsTagAttribute(description="Whether the result of this action (probably a view) should be executed/rendered", type="Boolean", defaultValue="false")
    public void setExecuteResult(boolean executeResult) {
        this.executeResult = executeResult;
    }

    @StrutsTagAttribute(description="Whether the request parameters are to be included when the action is invoked", type="Boolean", defaultValue="false")
    public void setIgnoreContextParams(boolean ignoreContextParams) {
        this.ignoreContextParams = ignoreContextParams;
    }

    @StrutsTagAttribute(description="Whether the writer should be flush upon end of action component tag, default to true", type="Boolean", defaultValue="true")
    public void setFlush(boolean flush) {
        this.flush = flush;
    }
}
