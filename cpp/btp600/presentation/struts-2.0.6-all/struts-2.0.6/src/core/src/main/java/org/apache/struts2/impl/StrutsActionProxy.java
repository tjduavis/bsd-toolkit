/*
 * $Id: StrutsActionProxy.java 506198 2007-02-12 00:57:44Z husted $
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
// Copyright 2006 Google Inc. All Rights Reserved.

package org.apache.struts2.impl;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.DefaultActionProxy;

import java.util.Map;

public class StrutsActionProxy extends DefaultActionProxy {

    private static final long serialVersionUID = -2434901249671934080L;

    public StrutsActionProxy(String namespace, String actionName, Map extraContext,
                             boolean executeResult, boolean cleanupContext) throws Exception {
        super(namespace, actionName, extraContext, executeResult, cleanupContext);
    }

    public String execute() throws Exception {
        ActionContext previous = ActionContext.getContext();
        ActionContext.setContext(invocation.getInvocationContext());
        try {
// This is for the new API:
//            return RequestContextImpl.callInContext(invocation, new Callable<String>() {
//                public String call() throws Exception {
//                    return invocation.invoke();
//                }
//            });
            
            return invocation.invoke();
        } finally {
            if (cleanupContext)
                ActionContext.setContext(previous);
        }
    }
}
