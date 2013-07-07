/*
 * $Id: Property.java 497654 2007-01-19 00:21:57Z rgielen $
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

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts2.views.annotations.StrutsTag;
import org.apache.struts2.views.annotations.StrutsTagAttribute;

import com.opensymphony.xwork2.util.ValueStack;
import com.opensymphony.xwork2.util.TextUtils;

/**
 * <!-- START SNIPPET: javadoc -->
 *
 * Used to get the property of a <i>value</i>, which will default to the top of
 * the stack if none is specified.
 *
 * <!-- END SNIPPET: javadoc -->
 *
 * <p/>
 *
 *
 * <!-- START SNIPPET: params -->
 *
 * <ul>
 *      <li>default (String) - The default value to be used if <u>value</u> attribute is null</li>
 *      <li>escape (Boolean) - Escape HTML. Default to true</li>
 *      <li>value (Object) - value to be displayed</li>
 * </ul>
 *
 * <!-- END SNIPPET: params -->
 *
 *
 * <pre>
 * <!-- START SNIPPET: example -->
 *
 * <s:push value="myBean">
 *     <!-- Example 1: -->
 *     <s:property value="myBeanProperty" />
 *
 *     <!-- Example 2: -->TextUtils
 *     <s:property value="myBeanProperty" default="a default value" />
 * </s:push>
 *
 * <!-- END SNIPPET: example -->
 * </pre>
 *
 * <pre>
 * <!-- START SNIPPET: exampledescription -->
 *
 * Example 1 prints the result of myBean's getMyBeanProperty() method.
 * Example 2 prints the result of myBean's getMyBeanProperty() method and if it is null, print 'a default value' instead.
 *
 * <!-- END SNIPPET: exampledescription -->
 * </pre>
 *
 *
 * <pre>
 * <!-- START SNIPPET: i18nExample -->
 *
 * &lt;s:property value="getText('some.key')" /&gt;
 *
 * <!-- END SNIPPET: i18nExample -->
 * </pre>
 *
 */
@StrutsTag(name="property", tldBodyContent="empty", tldTagClass="org.apache.struts2.views.jsp.PropertyTag",
    description="Print out expression which evaluates against the stack")
public class Property extends Component {
    private static final Log LOG = LogFactory.getLog(Property.class);

    public Property(ValueStack stack) {
        super(stack);
    }

    private String defaultValue;
    private String value;
    private boolean escape = true;

    @StrutsTagAttribute(description="The default value to be used if <u>value</u> attribute is null")
    public void setDefault(String defaultValue) {
        this.defaultValue = defaultValue;
    }

    @StrutsTagAttribute(description=" Whether to escape HTML", type="Boolean", defaultValue="true")
    public void setEscape(boolean escape) {
        this.escape = escape;
    }

    @StrutsTagAttribute(description="Value to be displayed", type="Object", defaultValue="&lt;top of stack&gt;")
    public void setValue(String value) {
        this.value = value;
    }

    public boolean start(Writer writer) {
        boolean result = super.start(writer);

        String actualValue = null;

        if (value == null) {
            value = "top";
        }
        else if (altSyntax()) {
            // the same logic as with findValue(String)
            // if value start with %{ and end with }, just cut it off!
            if (value.startsWith("%{") && value.endsWith("}")) {
                value = value.substring(2, value.length() - 1);
            }
        }

        // exception: don't call findString(), since we don't want the
        //            expression parsed in this one case. it really
        //            doesn't make sense, in fact.
        actualValue = (String) getStack().findValue(value, String.class);

        try {
            if (actualValue != null) {
                writer.write(prepare(actualValue));
            } else if (defaultValue != null) {
                writer.write(prepare(defaultValue));
            }
        } catch (IOException e) {
            LOG.info("Could not print out value '" + value + "'", e);
        }

        return result;
    }

    private String prepare(String value) {
        if (escape) {
            return TextUtils.htmlEncode(value);
        } else {
            return value;
        }
    }
}
