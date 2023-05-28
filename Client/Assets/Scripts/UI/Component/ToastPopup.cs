using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;

namespace Gravity.UI
{
    public class ToastPopup : MonoBehaviour
    {
        [SerializeField] private Text _messageText;

        private UnityAction<ToastPopup> _deleteCallback;
        private float _lifeTime;

        public void Update()
        {
            if (_lifeTime <= 0.0f)
                return;

            _lifeTime -= Time.unscaledDeltaTime;
            if (_lifeTime > 0.0f)
                return;

            DeleteMessage();
        }

        public void ShowMessage(string message, float lifeTime, UnityAction<ToastPopup> deleteCallback)
        {
            _messageText.text = message;
            _deleteCallback = deleteCallback;
            _lifeTime = lifeTime;
        }

        public void DeleteMessage()
        {
            _deleteCallback?.Invoke(this);
            _deleteCallback = null;
        }
    }
}