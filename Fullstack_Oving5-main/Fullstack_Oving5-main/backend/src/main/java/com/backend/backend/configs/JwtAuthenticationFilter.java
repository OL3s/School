package com.backend.backend.configs;

import java.io.IOException;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.web.authentication.WebAuthenticationDetailsSource;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;

import com.backend.backend.services.TokenService;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

@Component
public class JwtAuthenticationFilter extends OncePerRequestFilter {

    @Autowired
    private TokenService tokenService;

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain)
            throws ServletException, IOException {
        
        final String authorizationHeader = request.getHeader("Authorization");
        
        String username = null;
        String jwt = null;
        
        // Check if the authorization header is present and starts with "Bearer "
        if (authorizationHeader != null && authorizationHeader.startsWith("Bearer ")) {
            jwt = authorizationHeader.substring(7);
            
            // For guest token, create special authentication
            if ("guest".equals(jwt)) {
                UsernamePasswordAuthenticationToken guestAuth = new UsernamePasswordAuthenticationToken(
                    "guest", null, java.util.Collections.emptyList());
                guestAuth.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));
                SecurityContextHolder.getContext().setAuthentication(guestAuth);
            } else {
                try {
                    // Get username from token
                    username = tokenService.getUsernameFromToken(jwt);
                    
                    // Only set authentication if username is not null and not already authenticated
                    if (username != null && SecurityContextHolder.getContext().getAuthentication() == null) {
                        if (tokenService.isTokenValid(jwt)) {
                            UsernamePasswordAuthenticationToken auth = new UsernamePasswordAuthenticationToken(
                                username, null, java.util.Collections.emptyList());
                            auth.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));
                            SecurityContextHolder.getContext().setAuthentication(auth);
                        }
                    }
                } catch (Exception e) {
                    logger.warn("JWT token validation failed", e);
                }
            }
        }
        
        filterChain.doFilter(request, response);
    }
}
