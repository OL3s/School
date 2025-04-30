package com.backend.backend.services;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import io.jsonwebtoken.security.Keys;
import org.springframework.stereotype.Service;

import java.security.Key;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

@Service
public class TokenService {

    // In production, use a secure key stored in environment variables or config
    private static final Key secretKey = Keys.secretKeyFor(SignatureAlgorithm.HS256);
    
    // Token validity in milliseconds - 5 minutes
    private static final long JWT_TOKEN_VALIDITY = 5 * 60 * 1000;

    /**
     * Generate a JWT token for a user
     * @param username Username to include in the token
     * @return JWT token string
     */
    public String generateToken(String username) {
        Map<String, Object> claims = new HashMap<>();
        return createToken(claims, username);
    }

    /**
     * Validate a JWT token
     * @param token The token to validate
     * @param username The username to validate against
     * @return true if valid, false otherwise
     */
    public Boolean validateToken(String token, String username) {
        // For the "guest" token, always return true
        if ("guest".equals(token)) {
            return true;
        }
        
        // Check if token is in Bearer format
        if (token != null && token.startsWith("Bearer ")) {
            token = token.substring(7);
        }
        
        final String usernameFromToken = getUsernameFromToken(token);
        return (usernameFromToken.equals(username) && !isTokenExpired(token));
    }

    /**
     * Get the username from a token
     * @param token The token
     * @return The username
     */
    public String getUsernameFromToken(String token) {
        // Handle guest token
        if ("guest".equals(token)) {
            return "guest";
        }
        
        // Handle Bearer prefix
        if (token != null && token.startsWith("Bearer ")) {
            token = token.substring(7);
        }
        
        return getClaimFromToken(token, Claims::getSubject);
    }

    /**
     * Check if a token is valid (not expired)
     * @param token The token
     * @return true if the token is valid, false otherwise
     */
    public Boolean isTokenValid(String token) {
        // Handle guest token
        if ("guest".equals(token)) {
            return true;
        }
        
        // Handle Bearer prefix
        if (token != null && token.startsWith("Bearer ")) {
            token = token.substring(7);
        }
        
        try {
            return !isTokenExpired(token);
        } catch (Exception e) {
            return false;
        }
    }

    // Private helper methods
    
    private String createToken(Map<String, Object> claims, String subject) {
        return Jwts.builder()
            .setClaims(claims)
            .setSubject(subject)
            .setIssuedAt(new Date(System.currentTimeMillis()))
            .setExpiration(new Date(System.currentTimeMillis() + JWT_TOKEN_VALIDITY))
            .signWith(secretKey)
            .compact();
    }
    
    private <T> T getClaimFromToken(String token, Function<Claims, T> claimsResolver) {
        final Claims claims = getAllClaimsFromToken(token);
        return claimsResolver.apply(claims);
    }
    
    private Claims getAllClaimsFromToken(String token) {
        return Jwts.parserBuilder()
            .setSigningKey(secretKey)
            .build()
            .parseClaimsJws(token)
            .getBody();
    }
    
    private Boolean isTokenExpired(String token) {
        final Date expiration = getExpirationDateFromToken(token);
        return expiration.before(new Date());
    }
    
    private Date getExpirationDateFromToken(String token) {
        return getClaimFromToken(token, Claims::getExpiration);
    }
}