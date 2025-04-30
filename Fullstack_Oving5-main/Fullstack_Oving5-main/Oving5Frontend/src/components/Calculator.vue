<template>
    <div class="calculator">
        <h2>{{ display }}</h2>
        <!-- Calculator UI goes here -->
        <div class="buttons">
            <button 
                v-for="button in buttons" 
                :key="button" 
                @click="button === 'C' ? clearPressed() : button === '=' ? equalsPressed() : button === '+' || button === '-' || button === '*' || button === '/' ? operatorPressed(button) : numberPressed(button)">
                {{ button }}
            </button>
        </div>
    </div>
</template>

<script lang="ts">
import axios from 'axios';
import { ref } from 'vue';

export default {
    name: 'Calculator',
    setup() {
        // Reactive variables
        const buttons = ref<string[]>([
            '7', '8', '9', '/',
            '4', '5', '6', '*',
            '1', '2', '3', '-',
            'C', '0', '=', '+'
        ]);

        const display = ref<string>('clear');
        const inputs = ref<string[]>(['', '']);
        const operator = ref<string>('');

        // Methods
        const numberPressed = (number: string) => {
            if (operator.value === '') {
                inputs.value[0] += number;
                updateDisplay();
            } else {
                inputs.value[1] += number;
                display.value = inputs.value[1];
                updateDisplay();
            }
        };

        const operatorPressed = (op: string) => {
            operator.value = op;
            updateDisplay();
        };

        const clearPressed = () => {
            inputs.value = ['', ''];
            operator.value = '';
            display.value = 'cleared';
        };

        const updateDisplay = () => {
            display.value = inputs.value[0] + ' ' + operator.value + ' ' + inputs.value[1];
        };

        const equalsPressed = () => {

            // Check if the operator is set
            if (operator.value === '') {
                clearPressed();
                display.value = 'no operator';
                return;
            }

            // Check if the numbers is set
            if (inputs.value[1] === '' || inputs.value[0] === '') {
                clearPressed();
                display.value = 'missing number';
                return;
            }

            let adress = "http://localhost:8080/api/";

            // Get the right address for the operator
            switch (operator.value) {
                case '+':
                    adress += "add";
                    break;
                case '-':
                    adress += "subtract";
                    break;
                case '*':
                    adress += "multiply";
                    break;
                case '/':
                    adress += "divide";
                    break;
                default:
                    clearPressed();
                    display.value = 'invalid operator';
                    console.log("invalid operator");
                    return;
            }

            console.log(adress + " equalsPressed()");

            // Retrieve token
            const token = sessionStorage.getItem("token");
            if (token === null) {
                clearPressed();
                display.value = 'no token';
                return;
            }

            axios.post(adress, {
                num1: inputs.value[0],
                num2: inputs.value[1],
            }, {
                headers: { 
                    'Content-Type': 'application/json',
                    'Authorization': 'Bearer ' + token
                }
            }).then(response => {
                if (response.data.success) {
                    clearPressed();
                    display.value = response.data.result;
                } else {
                    clearPressed();
                    display.value = response.data.message ?? 'unknown error';
                }
            }).catch(error => {
                console.error(error);
                clearPressed();
                display.value = error instanceof Error ? error.message : 'An unknown error occurred';
            });
        };

        // Return variables and methods to the template
        return {
            buttons,
            display,
            numberPressed,
            operatorPressed,
            clearPressed,
            equalsPressed
        };
    }
};
</script>

<style scoped>
.calculator {
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 1rem;
}

.buttons {
    display: grid;
    grid-template-columns: repeat(4, 1fr);
    gap: 0.5rem;
}

button {
    padding: 1rem;
    font-size: 1.5rem;
    background-color: #61dafb;
    border: none;
    border-radius: 5px;
    cursor: pointer;
}

button:hover {
    background-color: #21a1f1;
}
</style>