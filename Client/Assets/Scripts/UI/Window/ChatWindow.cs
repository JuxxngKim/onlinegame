using System;
using System.Collections;
using System.Collections.Generic;
using deVoid.Utils;
using Protocol;
using UnityEngine;
using UnityEngine.UI;
using YeongJ;

public class ChatWindow : MonoBehaviour
{
    [SerializeField] InputField _inputField;
    [SerializeField] ScrollRect _scrollRect;
    [SerializeField] Text _templateChatText;
    [SerializeField] Text _imeIsSelectedText;
    [SerializeField] RectTransform _contentRoot;
    [SerializeField] RectTransform _bubbleRoot;
    [SerializeField] ChatBubble _templateChatBubble;
    
    public static bool InputLock = false;
    
    List<Text> _chatList = new List<Text>();
    Dictionary<int, ChatBubble> _chatBubbles = new Dictionary<int, ChatBubble>();

    private void Awake()
    {
        _inputField.onEndEdit.AddListener(SendChat);
        Signals.Get<AddChat>().AddListener(AddChat);
    }

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
    
    public void AddChat(int objectId, string userName, string userChat)
    {
        string chat = $"[{System.DateTime.Now.Hour:D2}:{System.DateTime.Now.Minute:D2}] {userName} : {userChat}";

        var newText =  GameObjectCache.Make<Text>(_templateChatText, _contentRoot);
        newText.text = chat;
        _chatList.Add(newText);

        LayoutRebuilder.ForceRebuildLayoutImmediate(_contentRoot);

        if (_chatBubbles.TryGetValue(objectId, out var bubble))
        {
            bubble.UpdateData(userChat);
        }
        else
        {
            var creatureController = Managers.Object.FindById(objectId)?.GetComponent<CreatureController>();
            if (creatureController == null)
                return;

            var newBubble = GameObjectCache.Make(_templateChatBubble, _bubbleRoot);
            _chatBubbles.Add(objectId, newBubble);

            _chatBubbles[objectId].SetUp(creatureController, userName, userChat, RemoveBubbleChat);
        }

        StartCoroutine(RefreshScrollPoisition());
    }
    
    System.Collections.IEnumerator RefreshScrollPoisition()
    {
        yield return new WaitForEndOfFrame();
        yield return new WaitForEndOfFrame();

        _scrollRect.verticalNormalizedPosition = 0.0f;
    }

    private void RemoveBubbleChat(int objectId)
    {
        if (_chatBubbles.ContainsKey(objectId))
        {
            GameObjectCache.Delete(_chatBubbles[objectId].transform);
            _chatBubbles.Remove(objectId);
        }
    }
}
