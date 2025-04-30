<template>
    <div>
        <p v-if="loginMessage">{{ loginMessage }} </p>
        <p></p>
    </div>
    <div>
        <form @submit.prevent="requestLogin">
        <input type="text" v-model="username" placeholder="Username" required />
        <input type="password" v-model="password" placeholder="Password" required />
        <div class="buttons">
            <button id="login-button" type="submit" @click="requestLogin">Login</button>
            <button id="guest-button" type="button" @click="requestGuest">Guest</button>
        </div>
        </form>
    </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { useRouter } from 'vue-router';
import axios from 'axios';

// Define reactive variables
const username = ref<string>('');
const password = ref<string>('');
const loginMessage = ref<string>('');

// Initialize router
const router = useRouter();

// Login request function
const requestLogin = async () => {
    try {

        // Request data container
        const requestData = {
            username: username.value,
            password: password.value
        };

        // Send request to backend
        const response = await axios.post("http://localhost:8080/api/auth/login", requestData, {
            headers: { 'Content-Type': 'application/json' }
        });

        // Set response logic
        /*
         * Signals from backend: (responcedata. is the response object)
            * - success: true if login was successful, false otherwise
            * - token: JWT token if login was successful
            * - message: error message if login was unsuccessful 
        */
        if (response.data.success) {
            loginMessage.value = "Login successful";
            sessionStorage.setItem("token", response.data.token);
            sessionStorage.setItem("username", username.value);
            router.push("/calculator");
        } else {
            loginMessage.value = "Login failed: " + (response.data.message ?? "unknown error");
        }

    // Catch error
    } catch (error) {
        console.error(error);
        const errorMessage = error instanceof Error ? error.message : "An unknown error occurred";
        loginMessage.value = "Login failed: " + errorMessage;
    }
};

// Guest login request function
const requestGuest = async () => {
    sessionStorage.setItem("token", "guest");
    router.push("/calculator");
};

</script>

<style scoped>
form {
    display: flex;
    flex-direction: column;
    gap: 1rem;
}
input {
    padding: 0.5rem;
    font-size: 1rem;
}
button {
    padding: 0.5rem;
    font-size: 1rem;
    background-color: #282c34;
    color: white;
    border: none;
    cursor: pointer;
}
.buttons {
    display: flex;
    justify-content: space-between;
    gap: 1rem;
}
#login-button {
    width: 100%;
}

#guest-button {
    width: 30%;
}
button:hover {
    background-color: #61dafb;
}
p {
    color: red;
}
</style>
