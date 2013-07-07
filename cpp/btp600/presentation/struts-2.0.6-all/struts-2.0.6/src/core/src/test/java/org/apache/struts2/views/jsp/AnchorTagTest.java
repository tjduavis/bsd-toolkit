/*
 * $Id: AnchorTagTest.java 471756 2006-11-06 15:01:43Z husted $
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

import java.io.StringWriter;

import javax.servlet.jsp.JspException;
import javax.servlet.jsp.JspWriter;

import org.apache.struts2.views.jsp.ui.AnchorTag;
import org.apache.struts2.views.jsp.ui.StrutsBodyContent;


/**
 *
 */
public class AnchorTagTest extends AbstractUITagTest {
    private StringWriter writer = new StringWriter();
    private AnchorTag tag;

    public void testActionURL() {
        tag.setHref("TestAction.action");
        try {
            tag.doStartTag();
            tag.doEndTag();
            assertTrue( writer.toString().indexOf("href=\"TestAction.action\"") > -1);
        } catch (JspException ex) {
            ex.printStackTrace();
            fail();
        }
    }

    public void testAddParameters() {
        tag.setHref("/TestAction.action");
        String bodyText = "<img src=\"#\"/>";
        try {
            StrutsBodyContent bodyContent = new StrutsBodyContent(null);
            bodyContent.print(bodyText);
            tag.setBodyContent(bodyContent);

            tag.doStartTag();
            tag.doEndTag();
        } catch (Exception ex) {
            ex.printStackTrace();
            fail();
        }
    }


    protected void setUp() throws Exception {
        super.setUp();

        request.setScheme("http");
        request.setServerName("localhost");
        request.setServerPort(80);

        tag = new AnchorTag();
        tag.setPageContext(pageContext);
        JspWriter jspWriter = new StrutsMockJspWriter(writer);
        pageContext.setJspWriter(jspWriter);
    }

}
