/*
 * $Id: CollectionAdapter.java 471756 2006-11-06 15:01:43Z husted $
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
package org.apache.struts2.views.xslt;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.w3c.dom.Node;


/**
 */
public class CollectionAdapter extends AbstractAdapterElement {

    private Log log = LogFactory.getLog(this.getClass());

    public CollectionAdapter() { }

    public CollectionAdapter(AdapterFactory rootAdapterFactory, AdapterNode parent, String propertyName, Object value) {
        setContext(rootAdapterFactory, parent, propertyName, value);
    }

    protected List<Node> buildChildAdapters() {
        Collection values = (Collection) getPropertyValue();
        List<Node> children = new ArrayList<Node>(values.size());

        for (Object value : values) {
            Node childAdapter = getAdapterFactory().adaptNode(this, "item", value);
            if (childAdapter != null)
                children.add(childAdapter);

            if (log.isDebugEnabled()) {
                log.debug(this + " adding adapter: " + childAdapter);
            }
        }

        return children;
    }
}
