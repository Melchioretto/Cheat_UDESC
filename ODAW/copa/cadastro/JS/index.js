const form = document.getElementById('form')
const username = document.getElementById('username')
const email = document.getElementById('email')
const cpf = document.getElementById('cpf')
const password = document.getElementById('password')
const passwordtwo = document.getElementById('password-two')


function checkInputs() {
    const usernameValue = username.value.trim()
    const emailValue = email.value.trim()
    const cpfValue = cpf.value.trim()
    const passwordValue = password.value.trim()
    const passwordtwoValue = passwordtwo.value.trim()

    var us = false
    var em = false
    var cp = false
    var pa1 = false
    var pa2 = false
    
    
    if(usernameValue === '') {
        // mostrar erro
        // add classe
        setErrorFor(username, 'Preencha esse campo')
    } else {
        // adicionar a classe de sucesso
        setSuccessFor(username)
        us = true
    }

    if(emailValue === '') {
        // mostrar erro
        // add classe
        setErrorFor(email, 'Preencha esse campo')
    } else if (!isEmail(emailValue)) {
        setErrorFor(email, 'Email inválido')
    } else {
        // adicionar a classe de sucesso
        setSuccessFor(email)
        em = true
    }
   
    if(cpfValue === ''){
        setErrorFor(cpf, 'Preencha esse campo')
    }else if(!isCPF(cpfValue) === false){
        setSuccessFor(cpf)
        cp = true
    }else{
        setErrorFor(cpf, 'Cpf invalido !')
        
    }



    if(passwordValue === '') {
        // mostrar erro
        // add classe
        setErrorFor(password, 'Preencha esse campo')

    } else if(passwordValue.length < 8) { 
        setErrorFor(password, 'Senha deve ter mais que 8 caracteres')
    } else {
        // adicionar a classe de sucesso
        setSuccessFor(password)
        pa1 = true
    }

    if(passwordtwoValue === '') {
        // mostrar erro
        // add classe
        setErrorFor(passwordtwo, 'Preencha esse campo')

    } else if(passwordValue !== passwordtwoValue) { 
        setErrorFor(passwordtwo, 'Senhas não tão iguais')
    } else {
        // adicionar a classe de sucesso
        setSuccessFor(passwordtwo)
        pa2 = true
    }
    if(us===true&&em===true&&cp===true&&pa1===true&&pa2===true){
        return true
    }else{
        return false
    }

}

function setErrorFor(input, message) {
    const formControl = input.parentElement;
    const small = formControl.querySelector('small')

    small.innerText = message

    formControl.className = 'form-control error'
}

function setSuccessFor(input) {
    const formControl = input.parentElement;

    formControl.className = 'form-control success'
}

function isEmail(email) {
    return /^(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])/.test(email)
}

function isCPF(cpf){
        var Soma;
        var Resto;
        Soma = 0;
    if (cpf == "00000000000") return false;

    for (i=1; i<=9; i++) Soma = Soma + parseInt(cpf.substring(i-1, i)) * (11 - i);
    Resto = (Soma * 10) % 11;

        if ((Resto == 10) || (Resto == 11))  Resto = 0;
        if (Resto != parseInt(cpf.substring(9, 10)) ) return false;

    Soma = 0;
        for (i = 1; i <= 10; i++) Soma = Soma + parseInt(cpf.substring(i-1, i)) * (12 - i);
        Resto = (Soma * 10) % 11;

        if ((Resto == 10) || (Resto == 11))  Resto = 0;
        if (Resto != parseInt(cpf.substring(10, 11) ) ) return false;
        return true;

}