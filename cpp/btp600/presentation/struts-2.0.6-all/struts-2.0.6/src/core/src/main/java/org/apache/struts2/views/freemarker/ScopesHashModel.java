/*
 * $Id: ScopesHashModel.java 471756 2006-11-06 15:01:43Z husted $
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
package org.apache.struts2.views.freemarker;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import com.opensymphony.xwork2.util.ValueStack;

import freemarker.template.ObjectWrapper;
import freemarker.template.SimpleHash;
import freemarker.template.TemplateModel;
import freemarker.template.TemplateModelException;


/**
 * Simple Hash model that also searches other scopes.
 * <p/>
 * If the key doesn't exist in this hash, this template model tries to
 * resolve the key within the attributes of the following scopes,
 * in the order stated: Request, Session, Servlet Context
 */
public class ScopesHashModel extends SimpleHash {

    private static final long serialVersionUID = 5551686380141886764L;

    private HttpServletRequest request;
    private ServletContext servletContext;
    private ValueStack stack;


    public ScopesHashModel(ObjectWrapper objectWrapper, ServletContext context, HttpServletRequest request, ValueStack stack) {
        super(objectWrapper);
        this.servletContext = context;
        this.request = request;
        this.stack = stack;
    }


    public TemplateModel get(String key) throws TemplateModelException {
        // Lookup in default scope
        TemplateModel model = super.get(key);

        if (model != null) {
            return model;
        }


        if (stack != null) {
            Object obj = stack.findValue(key);

            if (obj != null) {
                return wrap(obj);
            }

            // ok, then try the context
            obj = stack.getContext().get(key);
            if (obj != null) {
                return wrap(obj);
            }
        }

        if (request != null) {
            // Lookup in request scope
            Object obj = request.getAttribute(key);

            if (obj != null) {
                return wrap(obj);
            }

            // Lookup in session scope
            HttpSession session = request.getSession(false);

            if (session != null) {
                obj = session.getAttribute(key);

                if (obj != null) {
                    return wrap(obj);
                }
            }
        }

        if (servletContext != null) {
            // Lookup in application scope
            Object obj = servletContext.getAttribute(key);

            if (obj != null) {
                return wrap(obj);
            }
        }

        return null;
    }

    public void put(String string, boolean b) {
        super.put(string, b);
    }

    public void put(String string, Object object) {
        super.put(string, object);
    }
}
