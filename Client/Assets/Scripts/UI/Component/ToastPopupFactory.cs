using System;
using System.Collections;
using System.Collections.Generic;
using deVoid.Utils;
using UnityEngine;
using UnityEngine.UI;
using YeongJ;

namespace Gravity.UI
{
    public class ToastPopupFactory : MonoBehaviour
    {
        [SerializeField] private ToastPopup _templatePopup;
        [SerializeField] private RectTransform _popupRoot;
        [SerializeField] private float _lifeTime = 5.0f;

        private List<ToastPopup> _showPopups = new List<ToastPopup>();

        private readonly int _maxCount = 5;

        public void Awake()
        {
            Signals.Get<ShowToastMessage>().AddListener(ShowPopup);
        }

        public void ShowPopup(string message)
        {
            if (_showPopups.Count >= _maxCount)
            {
                _showPopups[0].DeleteMessage();
            }

            var newPopup = GameObjectCache.Make(_templatePopup, _popupRoot);
            newPopup.ShowMessage(message, _lifeTime, DeleteMessage);

            _showPopups.Add(newPopup);
            LayoutRebuilder.ForceRebuildLayoutImmediate(_popupRoot);
        }

        private void DeleteMessage(ToastPopup deletePopup)
        {
            if (_showPopups.Contains(deletePopup))
            {
                _showPopups.Remove(deletePopup);
            }

            GameObjectCache.Delete(deletePopup.transform);
        }
    }
}