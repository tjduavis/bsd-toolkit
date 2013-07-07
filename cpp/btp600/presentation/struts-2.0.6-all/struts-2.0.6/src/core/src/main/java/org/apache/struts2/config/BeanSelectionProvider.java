/*
 * $Id: BeanSelectionProvider.java 499704 2007-01-25 08:57:59Z mrdon $
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
package org.apache.struts2.config;

import java.util.Properties;
import java.util.StringTokenizer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts2.StrutsConstants;
import org.apache.struts2.StrutsException;
import org.apache.struts2.dispatcher.mapper.ActionMapper;
import org.apache.struts2.dispatcher.multipart.MultiPartRequest;
import org.apache.struts2.views.freemarker.FreemarkerManager;
import org.apache.struts2.views.velocity.VelocityManager;

import com.opensymphony.xwork2.ActionProxyFactory;
import com.opensymphony.xwork2.ObjectFactory;
import com.opensymphony.xwork2.config.Configuration;
import com.opensymphony.xwork2.config.ConfigurationException;
import com.opensymphony.xwork2.config.ConfigurationProvider;
import com.opensymphony.xwork2.inject.Container;
import com.opensymphony.xwork2.inject.ContainerBuilder;
import com.opensymphony.xwork2.inject.Context;
import com.opensymphony.xwork2.inject.Factory;
import com.opensymphony.xwork2.inject.Inject;
import com.opensymphony.xwork2.inject.Scope;
import com.opensymphony.xwork2.util.ClassLoaderUtil;
import com.opensymphony.xwork2.util.LocalizedTextUtil;
import com.opensymphony.xwork2.util.ObjectTypeDeterminer;
import com.opensymphony.xwork2.util.ObjectTypeDeterminerFactory;
import com.opensymphony.xwork2.util.XWorkConverter;
import com.opensymphony.xwork2.util.location.LocatableProperties;

/**
 * Selects the implementations of key framework extension points, using the loaded
 * property constants.  The implementations are selected from the container builder
 * using the name defined in its associated property.  The default implementation name will
 * always be "struts".
 *
 * <p>
 * The following is a list of the allowed extension points:
 *
 * <!-- START SNIPPET: extensionPoints -->
 * <table border="1">
 *   <tr>
 *     <th>Type</th>
 *     <th>Property</th>
 *     <th>Scope</th>
 *     <th>Description</th>
 *   </tr>
 *   <tr>
 *     <td>com.opensymphony.xwork2.ObjectFactory</td>
 *     <td>struts.objectFactory</td>
 *     <td>singleton</td>
 *     <td>Creates actions, results, and interceptors</td>
 *   </tr>
 *   <tr>
 *     <td>com.opensymphony.xwork2.ActionProxyFactory</td>
 *     <td>struts.actionProxyFactory</td>
 *     <td>singleton</td>
 *     <td>Creates the ActionProxy</td>
 *   </tr>
 *   <tr>
 *     <td>com.opensymphony.xwork2.util.ObjectTypeDeterminer</td>
 *     <td>struts.objectTypeDeterminer</td>
 *     <td>singleton</td>
 *     <td>Determines what the key and and element class of a Map or Collection should be</td>
 *   </tr>
 *   <tr>
 *     <td>org.apache.struts2.dispatcher.mapper.ActionMapper</td>
 *     <td>struts.mapper.class</td>
 *     <td>singleton</td>
 *     <td>Determines the ActionMapping from a request and a URI from an ActionMapping</td>
 *   </tr>
 *   <tr>
 *     <td>org.apache.struts2.dispatcher.multipart.MultiPartRequest</td>
 *     <td>struts.multipart.parser</td>
 *     <td>per request</td>
 *     <td>Parses a multipart request (file upload)</td>
 *   </tr>
 *   <tr>
 *     <td>org.apache.struts2.views.freemarker.FreemarkerManager</td>
 *     <td>struts.freemarker.manager.classname</td>
 *     <td>singleton</td>
 *     <td>Loads and processes Freemarker templates</td>
 *   </tr>
 *   <tr>
 *     <td>org.apache.struts2.views.velocity.VelocityManager</td>
 *     <td>struts.velocity.manager.classname</td>
 *     <td>singleton</td>
 *     <td>Loads and processes Velocity templates</td>
 *   </tr>
 * </table>
 *
 * <!-- END SNIPPET: extensionPoints -->
 * </p>
 * <p>
 * Implementations are selected using the value of its associated property.  That property is
 * used to determine the implementation by:
 * </p>
 * <ol>
 *   <li>Trying to find an existing bean by that name in the container</li>
 *   <li>Trying to find a class by that name, then creating a new bean factory for it</li>
 *   <li>Creating a new delegation bean factory that delegates to the configured ObjectFactory at runtime</li>
 * </ol>
 * <p>
 * Finally, this class overrides certain properties if dev mode is enabled:
 * </p>
 * <ul>
 *   <li><code>struts.i18n.reload = true</code></li>
 *   <li><code>struts.configuration.xml.reload = true</code></li>
 * </ul>
 */
public class BeanSelectionProvider implements ConfigurationProvider {
    public static final String DEFAULT_BEAN_NAME = "struts";
    private static final Log LOG = LogFactory.getLog(BeanSelectionProvider.class);
    
    public void destroy() {
        // NO-OP
    }

    public void loadPackages() throws ConfigurationException {
        // NO-OP
    }
    
    public void init(Configuration configuration) throws ConfigurationException {
        // NO-OP
        
    }

    public boolean needsReload() {
        return false;
    }

    public void register(ContainerBuilder builder, LocatableProperties props) {
        alias(ObjectFactory.class, StrutsConstants.STRUTS_OBJECTFACTORY, builder, props);
        alias(XWorkConverter.class, StrutsConstants.STRUTS_XWORKCONVERTER, builder, props);
        alias(ActionProxyFactory.class, StrutsConstants.STRUTS_ACTIONPROXYFACTORY, builder, props);
        alias(ObjectTypeDeterminer.class, StrutsConstants.STRUTS_OBJECTTYPEDETERMINER, builder, props);
        alias(ActionMapper.class, StrutsConstants.STRUTS_MAPPER_CLASS, builder, props);
        alias(MultiPartRequest.class, StrutsConstants.STRUTS_MULTIPART_PARSER, builder, props, Scope.DEFAULT);
        alias(FreemarkerManager.class, StrutsConstants.STRUTS_FREEMARKER_MANAGER_CLASSNAME, builder, props);
        alias(VelocityManager.class, StrutsConstants.STRUTS_VELOCITY_MANAGER_CLASSNAME, builder, props);
        
        if ("true".equalsIgnoreCase(props.getProperty(StrutsConstants.STRUTS_DEVMODE))) {
            props.setProperty(StrutsConstants.STRUTS_I18N_RELOAD, "true");
            props.setProperty(StrutsConstants.STRUTS_CONFIGURATION_XML_RELOAD, "true");
            // Convert struts properties into ones that xwork expects
            props.setProperty("devMode", "true");
        } else {
            props.setProperty("devMode", "false");
        }
        
        // TODO: This should be moved to XWork after 2.0.4
        // struts.custom.i18n.resources

        LocalizedTextUtil.addDefaultResourceBundle("org/apache/struts2/struts-messages");
        
        String bundles = props.getProperty(StrutsConstants.STRUTS_CUSTOM_I18N_RESOURCES);
        if (bundles != null && bundles.length() > 0) { 
            StringTokenizer customBundles = new StringTokenizer(props.getProperty(StrutsConstants.STRUTS_CUSTOM_I18N_RESOURCES), ", ");
            
            while (customBundles.hasMoreTokens()) {
                String name = customBundles.nextToken();
                try {
                    LOG.info("Loading global messages from " + name);
                    LocalizedTextUtil.addDefaultResourceBundle(name);
                } catch (Exception e) {
                    LOG.error("Could not find messages file " + name + ".properties. Skipping");
                }
            } 
        }
    }
    
    void alias(Class type, String key, ContainerBuilder builder, Properties props) {
        alias(type, key, builder, props, Scope.SINGLETON);
    }
    
    void alias(Class type, String key, ContainerBuilder builder, Properties props, Scope scope) {
        if (!builder.contains(type)) {
            String foundName = props.getProperty(key, DEFAULT_BEAN_NAME);
            if (builder.contains(type, foundName)) {
                if (LOG.isDebugEnabled()) {
                    LOG.info("Choosing bean ("+foundName+") for "+type);
                }
                builder.alias(type, foundName, Container.DEFAULT_NAME);
            } else {
                try {
                    Class cls = ClassLoaderUtil.loadClass(foundName, this.getClass());
                    if (LOG.isDebugEnabled()) {
                        LOG.debug("Choosing bean ("+cls+") for "+type);
                    }
                    builder.factory(type, cls, scope);
                } catch (ClassNotFoundException ex) {
                    // Perhaps a spring bean id, so we'll delegate to the object factory at runtime
                    if (LOG.isDebugEnabled()) {
                        LOG.debug("Choosing bean ("+foundName+") for "+type+" to be loaded from the ObjectFactory");
                    }
                    if (DEFAULT_BEAN_NAME.equals(foundName)) {
                        // Probably an optional bean, will ignore
                    } else {
                        if (ObjectFactory.class != type) {
                            builder.factory(type, new ObjectFactoryDelegateFactory(foundName, type), scope);
                        } else {
                            throw new ConfigurationException("Cannot locate the chosen ObjectFactory implementation: "+foundName);
                        }
                    }
                }
            }
        } else {
            LOG.warn("Unable to alias bean type "+type+", default mapping already assigned.");
        }
    }
    
    class ObjectFactoryDelegateFactory implements Factory {
        String name;
        Class type;
        ObjectFactoryDelegateFactory(String name, Class type) {
            this.name = name;
            this.type = type;
        }
        
        public Object create(Context context) throws Exception {
            ObjectFactory objFactory = context.getContainer().getInstance(ObjectFactory.class);
            try {
                return objFactory.buildBean(name, null, true);
            } catch (ClassNotFoundException ex) {
                throw new ConfigurationException("Unable to load bean "+type.getName()+" ("+name+")");
            }
        }
    }
}
