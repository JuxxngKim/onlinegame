// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Enum.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Enum_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Enum_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Enum_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

enum PlayerType : int {
  PLAYER_TYPE_NONE = 0,
  PLAYER_TYPE_KNIGHT = 1,
  PLAYER_TYPE_MAGE = 2,
  PLAYER_TYPE_ARCHER = 3,
  PlayerType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  PlayerType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool PlayerType_IsValid(int value);
constexpr PlayerType PlayerType_MIN = PLAYER_TYPE_NONE;
constexpr PlayerType PlayerType_MAX = PLAYER_TYPE_ARCHER;
constexpr int PlayerType_ARRAYSIZE = PlayerType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PlayerType_descriptor();
template<typename T>
inline const std::string& PlayerType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PlayerType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PlayerType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PlayerType_descriptor(), enum_t_value);
}
inline bool PlayerType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, PlayerType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PlayerType>(
    PlayerType_descriptor(), name, value);
}
enum CreatureState : int {
  IDLE = 0,
  MOVING = 1,
  SKILL = 2,
  DEAD = 3,
  CreatureState_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  CreatureState_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool CreatureState_IsValid(int value);
constexpr CreatureState CreatureState_MIN = IDLE;
constexpr CreatureState CreatureState_MAX = DEAD;
constexpr int CreatureState_ARRAYSIZE = CreatureState_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* CreatureState_descriptor();
template<typename T>
inline const std::string& CreatureState_Name(T enum_t_value) {
  static_assert(::std::is_same<T, CreatureState>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function CreatureState_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    CreatureState_descriptor(), enum_t_value);
}
inline bool CreatureState_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, CreatureState* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<CreatureState>(
    CreatureState_descriptor(), name, value);
}
enum MoveDir : int {
  UP = 0,
  DOWN = 1,
  LEFT = 2,
  RIGHT = 3,
  MoveDir_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  MoveDir_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool MoveDir_IsValid(int value);
constexpr MoveDir MoveDir_MIN = UP;
constexpr MoveDir MoveDir_MAX = RIGHT;
constexpr int MoveDir_ARRAYSIZE = MoveDir_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MoveDir_descriptor();
template<typename T>
inline const std::string& MoveDir_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MoveDir>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MoveDir_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MoveDir_descriptor(), enum_t_value);
}
inline bool MoveDir_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, MoveDir* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MoveDir>(
    MoveDir_descriptor(), name, value);
}
enum GameObjectType : int {
  NONE = 0,
  PLAYER = 1,
  MONSTER = 2,
  PROJECTILE = 3,
  GameObjectType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  GameObjectType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool GameObjectType_IsValid(int value);
constexpr GameObjectType GameObjectType_MIN = NONE;
constexpr GameObjectType GameObjectType_MAX = PROJECTILE;
constexpr int GameObjectType_ARRAYSIZE = GameObjectType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* GameObjectType_descriptor();
template<typename T>
inline const std::string& GameObjectType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, GameObjectType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function GameObjectType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    GameObjectType_descriptor(), enum_t_value);
}
inline bool GameObjectType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, GameObjectType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<GameObjectType>(
    GameObjectType_descriptor(), name, value);
}
enum SkillType : int {
  SKILL_NONE = 0,
  SKILL_AUTO = 1,
  SKILL_PROJECTILE = 2,
  SkillType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  SkillType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool SkillType_IsValid(int value);
constexpr SkillType SkillType_MIN = SKILL_NONE;
constexpr SkillType SkillType_MAX = SKILL_PROJECTILE;
constexpr int SkillType_ARRAYSIZE = SkillType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* SkillType_descriptor();
template<typename T>
inline const std::string& SkillType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, SkillType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function SkillType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    SkillType_descriptor(), enum_t_value);
}
inline bool SkillType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, SkillType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<SkillType>(
    SkillType_descriptor(), name, value);
}
enum PlayerServerState : int {
  SERVER_STATE_LOGIN = 0,
  SERVER_STATE_LOBBY = 1,
  SERVER_STATE_GAME = 2,
  PlayerServerState_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  PlayerServerState_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool PlayerServerState_IsValid(int value);
constexpr PlayerServerState PlayerServerState_MIN = SERVER_STATE_LOGIN;
constexpr PlayerServerState PlayerServerState_MAX = SERVER_STATE_GAME;
constexpr int PlayerServerState_ARRAYSIZE = PlayerServerState_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PlayerServerState_descriptor();
template<typename T>
inline const std::string& PlayerServerState_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PlayerServerState>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PlayerServerState_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PlayerServerState_descriptor(), enum_t_value);
}
inline bool PlayerServerState_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, PlayerServerState* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PlayerServerState>(
    PlayerServerState_descriptor(), name, value);
}
enum ItemType : int {
  ITEM_TYPE_NONE = 0,
  ITEM_TYPE_WEAPON = 1,
  ITEM_TYPE_ARMOR = 2,
  ITEM_TYPE_CONSUMABLE = 3,
  ItemType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ItemType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ItemType_IsValid(int value);
constexpr ItemType ItemType_MIN = ITEM_TYPE_NONE;
constexpr ItemType ItemType_MAX = ITEM_TYPE_CONSUMABLE;
constexpr int ItemType_ARRAYSIZE = ItemType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ItemType_descriptor();
template<typename T>
inline const std::string& ItemType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ItemType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ItemType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ItemType_descriptor(), enum_t_value);
}
inline bool ItemType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ItemType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ItemType>(
    ItemType_descriptor(), name, value);
}
enum WeaponType : int {
  WEAPON_TYPE_NONE = 0,
  WEAPON_TYPE_SWORD = 1,
  WEAPON_TYPE_BOW = 2,
  WeaponType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  WeaponType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool WeaponType_IsValid(int value);
constexpr WeaponType WeaponType_MIN = WEAPON_TYPE_NONE;
constexpr WeaponType WeaponType_MAX = WEAPON_TYPE_BOW;
constexpr int WeaponType_ARRAYSIZE = WeaponType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* WeaponType_descriptor();
template<typename T>
inline const std::string& WeaponType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, WeaponType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function WeaponType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    WeaponType_descriptor(), enum_t_value);
}
inline bool WeaponType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, WeaponType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<WeaponType>(
    WeaponType_descriptor(), name, value);
}
enum ArmorType : int {
  ARMOR_TYPE_NONE = 0,
  ARMOR_TYPE_HELMET = 1,
  ARMOR_TYPE_ARMOR = 2,
  ARMOR_TYPE_BOOTS = 3,
  ArmorType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ArmorType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ArmorType_IsValid(int value);
constexpr ArmorType ArmorType_MIN = ARMOR_TYPE_NONE;
constexpr ArmorType ArmorType_MAX = ARMOR_TYPE_BOOTS;
constexpr int ArmorType_ARRAYSIZE = ArmorType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ArmorType_descriptor();
template<typename T>
inline const std::string& ArmorType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ArmorType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ArmorType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ArmorType_descriptor(), enum_t_value);
}
inline bool ArmorType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ArmorType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ArmorType>(
    ArmorType_descriptor(), name, value);
}
enum ConsumableType : int {
  CONSUMABLE_TYPE_NONE = 0,
  CONSUMABLE_TYPE_POTION = 1,
  ConsumableType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ConsumableType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ConsumableType_IsValid(int value);
constexpr ConsumableType ConsumableType_MIN = CONSUMABLE_TYPE_NONE;
constexpr ConsumableType ConsumableType_MAX = CONSUMABLE_TYPE_POTION;
constexpr int ConsumableType_ARRAYSIZE = ConsumableType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ConsumableType_descriptor();
template<typename T>
inline const std::string& ConsumableType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ConsumableType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ConsumableType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ConsumableType_descriptor(), enum_t_value);
}
inline bool ConsumableType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ConsumableType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ConsumableType>(
    ConsumableType_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::Protocol::PlayerType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::PlayerType>() {
  return ::Protocol::PlayerType_descriptor();
}
template <> struct is_proto_enum< ::Protocol::CreatureState> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::CreatureState>() {
  return ::Protocol::CreatureState_descriptor();
}
template <> struct is_proto_enum< ::Protocol::MoveDir> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::MoveDir>() {
  return ::Protocol::MoveDir_descriptor();
}
template <> struct is_proto_enum< ::Protocol::GameObjectType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::GameObjectType>() {
  return ::Protocol::GameObjectType_descriptor();
}
template <> struct is_proto_enum< ::Protocol::SkillType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::SkillType>() {
  return ::Protocol::SkillType_descriptor();
}
template <> struct is_proto_enum< ::Protocol::PlayerServerState> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::PlayerServerState>() {
  return ::Protocol::PlayerServerState_descriptor();
}
template <> struct is_proto_enum< ::Protocol::ItemType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::ItemType>() {
  return ::Protocol::ItemType_descriptor();
}
template <> struct is_proto_enum< ::Protocol::WeaponType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::WeaponType>() {
  return ::Protocol::WeaponType_descriptor();
}
template <> struct is_proto_enum< ::Protocol::ArmorType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::ArmorType>() {
  return ::Protocol::ArmorType_descriptor();
}
template <> struct is_proto_enum< ::Protocol::ConsumableType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::ConsumableType>() {
  return ::Protocol::ConsumableType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
