using System.Collections;
using System.Collections.Generic;
using Protocol;
using UnityEngine;
using UnityEngine.UI;

public class ChatWindow : MonoBehaviour
{
    [SerializeField] InputField _inputField;
    [SerializeField] ScrollRect _scrollRect;
    [SerializeField] Text _templateChatText;
    [SerializeField] Text _imeIsSelectedText;
    [SerializeField] RectTransform _contentRoot;
    [SerializeField] RectTransform _bubbleRoot;
    // [SerializeField] ChatBubble _templateChatBubble;
    
    public static bool InputLock = false;
    
    public void Update()
    {
        if(Input.GetKeyDown(KeyCode.Return) && _inputField.gameObject.activeInHierarchy)
        {
            if(!_inputField.isFocused)
            {
                _inputField.ActivateInputField();
                _inputField.Select();
            }
        }

        if (_inputField.gameObject.activeInHierarchy)
        {
            _imeIsSelectedText.text = Input.imeIsSelected ? "가" : "a";
        }

        InputLock = _inputField.isFocused && _inputField.gameObject.activeInHierarchy;
    }
    
    public void SendChat(string text)
    {
        var userChat = text;
        if (userChat == string.Empty)
            return;

        C_Chat chatPacket = new C_Chat();
        chatPacket.Message = text;
        Managers.Network.Send(chatPacket);
            
        _inputField.text = string.Empty;
        _inputField.ActivateInputField();
        _inputField.Select();
    }
}
