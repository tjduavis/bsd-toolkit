package org.apache.struts2.portlet.interceptor;

import org.apache.struts2.interceptor.PrincipalProxy;

import javax.portlet.PortletRequest;
import javax.servlet.http.HttpServletRequest;
import java.security.Principal;

/**
 * PrincipalProxy implementation for using PortletRequest Principal related methods.
 */
public class PortletPrincipalProxy implements PrincipalProxy {

    private PortletRequest request;

    /**
     * Constructs a proxy
     *
     * @param request The underlying request
     */
    public PortletPrincipalProxy(PortletRequest request) {
        this.request = request;
    }

    /**
     * True if the user is in the given role
     *
     * @param role The role
     * @return True if the user is in that role
     */
    public boolean isUserInRole(String role) {
        return request.isUserInRole(role);
    }

    /**
     * Gets the user principal
     *
     * @return The principal
     */
    public Principal getUserPrincipal() {
        return request.getUserPrincipal();
    }

    /**
     * Gets the user id
     *
     * @return The user id
     */
    public String getRemoteUser() {
        return request.getRemoteUser();
    }

    /**
     * Is the request using https?
     *
     * @return True if using https
     */
    public boolean isRequestSecure() {
        return request.isSecure();
    }

    /**
     * Gets the request.
     *
     * @return The request
     * @throws UnsupportedOperationException not supported in this implementation.
     * @deprecated To obtain the HttpServletRequest in your action, use
     *             {@link org.apache.struts2.servlet.ServletRequestAware}, since this method will be dropped in future.
     */
    public HttpServletRequest getRequest() {
        throw new UnsupportedOperationException("Usage of getRequest() method is deprecadet and not supported for this implementation");
    }
}
