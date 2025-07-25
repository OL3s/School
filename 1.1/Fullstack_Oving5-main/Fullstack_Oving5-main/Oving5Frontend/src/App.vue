<template>
  <header>
    <nav>
      <h1>Calculator App</h1>
    </nav>
  </header>
  <router-view />
</template>

<script setup lang="ts"></script>

<style>
header {
  background-color: #282c34;
  padding: 1rem;
  color: white;
}
nav a {
  color: white;
  margin: 0 10px;
  text-decoration: none;
}
</style>