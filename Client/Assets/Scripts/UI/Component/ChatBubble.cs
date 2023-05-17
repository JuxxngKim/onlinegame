using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;

public class ChatBubble : MonoBehaviour
{
    [SerializeField] RectTransform _bubbleRoot;
    [SerializeField] Text _nameText;
    [SerializeField] Text _chatText;
    [SerializeField] float _remainTime;

    private int _objectId;
    private Vector3 _currentVelocity = Vector3.zero;
    private UnityAction<int> _completeCallback;
    private CreatureController _creatureController;

    public void SetUp(CreatureController creatureController, string userName, string chatText,
        UnityAction<int> completeCallback)
    {
        _creatureController = creatureController;
        _nameText.text = userName;
        _chatText.text = chatText;
        _remainTime = 3.0f;
        _completeCallback = completeCallback;
        _objectId = _creatureController.Id;

        LayoutRebuilder.ForceRebuildLayoutImmediate(_bubbleRoot);

        this.transform.position = Camera.main.WorldToScreenPoint(_creatureController.UIRoot.transform.position);
    }

    public void UpdateData(string chatText)
    {
        _remainTime = 3.0f;
        _chatText.text = chatText;

        LayoutRebuilder.ForceRebuildLayoutImmediate(_bubbleRoot);
    }

    void Update()
    {
        UpdateChat();

        _remainTime -= Time.deltaTime;
        if (_remainTime <= 0f)
        {
            _completeCallback?.Invoke(_objectId);
            _completeCallback = null;
        }
    }

    void UpdateChat()
    {
        if (_creatureController == null)
            return;

        var velocity = Vector3.zero;

        var targetPosition = Camera.main.WorldToScreenPoint(_creatureController.UIRoot.transform.position);
        this.transform.position = Vector3.SmoothDamp(this.transform.position, targetPosition, ref velocity, 0.01f);
    }
}