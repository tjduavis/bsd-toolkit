/*
 * $Id: ServletContextHolderListenerTest.java 471756 2006-11-06 15:01:43Z husted $
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
package org.apache.struts2.portlet.context;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;

import junit.framework.TestCase;

import org.easymock.MockControl;

/**
 */
public class ServletContextHolderListenerTest extends TestCase {

    public void testContextInitialized() {
        MockControl mockContext = MockControl.createNiceControl(ServletContext.class);
        ServletContext context = (ServletContext)mockContext.getMock();
        ServletContextEvent event = new ServletContextEvent(context);
        ServletContextHolderListener listener = new ServletContextHolderListener();
        listener.contextInitialized(event);
        assertSame(ServletContextHolderListener.getServletContext(), context);

        listener.contextDestroyed(event);
        assertNull(ServletContextHolderListener.getServletContext());
    }

}
