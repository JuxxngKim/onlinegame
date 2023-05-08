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
        
        C_CreatePlayer createPlayer = new C_CreatePlayer();
        Managers.Network.Send(createPlayer);
    }

    private void OnClickLoginButton()
    {
        if (_accountInputField.text.Length <= 0 || _passwordInputField.text.Length <= 0)
            return;
        
        C_Login loginPacket = new C_Login();
        Managers.Network.Send(loginPacket);
    }
}
