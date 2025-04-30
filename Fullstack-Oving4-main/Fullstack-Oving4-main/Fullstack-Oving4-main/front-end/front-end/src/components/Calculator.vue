<script setup lang="ts">
import { ref } from 'vue'

const buttonStrings = ['7', '8', '9', '+', '4', '5', '6', '-', '1', '2', '3', '*', 'C', '0', '=', '/']

const inputA = ref('')
const inputB = ref('')  
const operator = ref('')
const output = ref('')
const state = ref('inputA')
const debug = ref(true)
const errorMessages = ref('')
const jsonRecived = ref('')
const jsonSent = ref('')

// set backend url
const getBackendUrl = () => {
  switch (operator.value) {
    case '+':
      return 'http://localhost:8080/add'
    case '-':
      return 'http://localhost:8080/subtract'
    case '*':
      return 'http://localhost:8080/multiply'
    case '/':
      return 'http://localhost:8080/divide'
    default:
      return ''
  }
}

// function to calculate the result of the input on the backend
const backendCalculate = async () => {
  const backendUrl = getBackendUrl()
  if (!backendUrl) {
    output.value = 'Error'
    errorMessages.value = 'Invalid operator'
    state.value = 'answer-receive'
    return
  }

  const requestData = {
    inputA: parseFloat(inputA.value),
    inputB: parseFloat(inputB.value)
  }
  jsonSent.value = JSON.stringify(requestData)

  try {
    const response = await fetch(backendUrl, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(requestData)
    })
    if (!response.ok) {
      throw new Error('Network response was not ok')
    }
    const data = await response.json()
    jsonRecived.value = JSON.stringify(data)
    output.value = data
  } catch (error) {
    console.error(error)
    output.value = 'Error'
    errorMessages.value = error.toString()
  } finally {
    state.value = 'answer-receive'
  }
}

// function to handle button clicks on calculator
const buttonClicked = (buttonString: string) => {
  // if number is pressed
  if (!isNaN(Number(buttonString))) {
    switch (state.value) {
      case 'inputA':
        if (inputA.value === '0') {
          inputA.value = buttonString
        } else {
          inputA.value += buttonString
        }
        break
      case 'inputB':
        if (inputB.value === '0') {
          inputB.value = buttonString
        } else {
          inputB.value += buttonString
        }
        break
      default:
        inputA.value = buttonString
        state.value = 'inputA'
        inputB.value = ''
        operator.value = ''
        break
    }
  }

  // if operator is pressed
  else if (['+', '-', '*', '/'].includes(buttonString)) {
    operator.value = buttonString
    state.value = 'inputB'
  } 

  // if clear is pressed
  else if (buttonString === 'C') {
    inputA.value = ''
    inputB.value = ''
    operator.value = ''
    output.value = ''
    state.value = 'inputA'
  }

  // if equals is pressed
  else if (buttonString === '=' && inputA.value !== '' && inputB.value !== '' && operator.value !== '') {
    state.value = 'answer-push'
    output.value = 'calculating...'

    // connect springboot backend
    backendCalculate()
  }
}

const displayText = () => {
  if (state.value === 'answer-push') return 'Calculating...'
  else if (state.value === 'answer-receive') return output.value
  else if (inputA.value || operator.value || inputB.value)
    return inputA.value + operator.value + inputB.value
  else return '0'
}
</script>

<template>
  <div id="calc">
    <div id="debug" v-if="debug">
      <h3>DEBUGGER: ENABLED</h3>
      <p>http -> {{ getBackendUrl() }} </p>
      <p>inputA: {{ inputA }}</p>
      <p>inputB: {{ inputB }}</p>
      <p>operator: {{ operator }}</p>
      <p>output: {{ output }}</p>
      <p>state: {{ state }}</p>
      <p>errorMessages: {{ errorMessages }}</p>
      <p>jsonSent: {{ jsonSent }}</p>
      <p>jsonRecived: {{ jsonRecived }}</p>
    </div>
    <div id="calc_display">
      <label>{{ displayText() }} </label>
    </div>
    <div id="calc_buttons">
      <button v-for="buttonString in buttonStrings" :key="buttonString" @click="buttonClicked(buttonString)">
        {{ buttonString }}
      </button>
    </div>
  </div>
</template>

<style>
#calc_display {
  display: flex;
  justify-content: center;
  align-items: center;
  font-size: 2em;
  margin: 1em;
  width: 300px;
  background-color: lightgray;
  border-radius: 10px;
  border: 4px solid #282c34;
  padding: 10px;
  color: #282c34;
}
#debug {
  background-color: gray;
  margin: 1em;
  padding: 10px;
  border-radius: 5px;
}
#calc {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  font-size: 1em;
  color: white;
}
#calc_buttons {
  display: grid;
  grid-template-columns: repeat(4, 1fr);
  gap: 10px;
  margin: 1em;
}
#calc_buttons button {
  background-color: #282c34;
  border: none;
  border-radius: 10px;
  padding: 20px;
  font-size: 1.5em;
  cursor: pointer;
}
#calc_buttons button:hover {
  background-color: deepskyblue;
}
</style>