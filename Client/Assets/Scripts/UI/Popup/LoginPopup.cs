using System;
using System.Collections;
using System.Collections.Generic;
using Protocol;
using UnityEngine;
using UnityEngine.UI;

public class LoginPopup : MonoBehaviour
{
    [SerializeField] private InputField _accountInputField;
    [SerializeField] private InputField _passwordInputField;
    
    [SerializeField] private Button _createAccountButton;
    [SerializeField] private Button _loginButton;
    
    private void Awake()
    {
        if (_createAccountButton != null)
            _createAccountButton.onClick.AddListener(OnClickCreateAccountButton);

        if (_loginButton != null)
            _loginButton.onClick.AddListener(OnClickLoginButton);
    }

    private void OnClickCreateAccountButton()
    {
        if (_accountInputField.text.Length <= 0 || _passwordInputField.text.Length <= 0)
            return;
        
        C_CreateAccount createPacket = new C_CreateAccount();
        createPacket.Id = _accountInputField.text;
        createPacket.Password = _passwordInputField.text;
        
        Managers.Network.Send(createPacket);
    }

    private void OnClickLoginButton()
    {
        if (_accountInputField.text.Length <= 0 || _passwordInputField.text.Length <= 0)
            return;
        
        C_Login loginPacket = new C_Login();
        loginPacket.Id = _accountInputField.text;
        loginPacket.Password = _passwordInputField.text;
        Managers.Network.Send(loginPacket);
    }

    public void ClearIdInfo()
    {
        _accountInputField.text = string.Empty;
        _passwordInputField.text = string.Empty;
    }
}
