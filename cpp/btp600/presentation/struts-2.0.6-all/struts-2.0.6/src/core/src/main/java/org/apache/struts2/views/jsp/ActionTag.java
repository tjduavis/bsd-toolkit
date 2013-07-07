/*
 * $Id: ActionTag.java 471756 2006-11-06 15:01:43Z husted $
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
package org.apache.struts2.views.jsp;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts2.components.ActionComponent;
import org.apache.struts2.components.Component;

import com.opensymphony.xwork2.util.ValueStack;

/**
 * @see ActionComponent
 */
public class ActionTag extends ComponentTagSupport {

    private static final long serialVersionUID = -5384167073331678855L;

    protected String name;
    protected String namespace;
    protected boolean executeResult;
    protected boolean ignoreContextParams;
    protected boolean flush = true;

    public Component getBean(ValueStack stack, HttpServletRequest req, HttpServletResponse res) {
        return new ActionComponent(stack, req, res);
    }

    protected void populateParams() {
        super.populateParams();

        ActionComponent action = (ActionComponent) component;
        action.setName(name);
        action.setNamespace(namespace);
        action.setExecuteResult(executeResult);
        action.setIgnoreContextParams(ignoreContextParams);
        action.setFlush(flush);
        action.start(pageContext.getOut());
    }

    protected void addParameter(String name, Object value) {
        ActionComponent ac = (ActionComponent) component;
        ac.addParameter(name, value);
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setNamespace(String namespace) {
        this.namespace = namespace;
    }

    public void setExecuteResult(boolean executeResult) {
        this.executeResult = executeResult;
    }

    public void setIgnoreContextParams(boolean ignoreContextParams) {
        this.ignoreContextParams = ignoreContextParams;
    }

    public void setFlush(boolean flush) {
        this.flush = flush;
    }

    public boolean getFlush() {
        return this.flush;
    }
}
