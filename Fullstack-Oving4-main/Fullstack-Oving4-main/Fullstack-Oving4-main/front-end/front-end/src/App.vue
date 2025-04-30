<script setup lang="ts">
import calculator from './components/Calculator.vue'
</script>

<template>
  <header class="App-header">
    <div>
      CALCULATOR APP
    </div>
  </header>
  <calculator/>
</template>

<style>
.App-header {
  background-color: #282c34;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  font-size: calc(10px + 2vmin);
  color: white;
}
</style>
