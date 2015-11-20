// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mysqlx_session.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "mysqlx_session.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Mysqlx {
namespace Session {

namespace {

const ::google::protobuf::Descriptor* AuthenticateStart_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AuthenticateStart_reflection_ = NULL;
const ::google::protobuf::Descriptor* AuthenticateContinue_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AuthenticateContinue_reflection_ = NULL;
const ::google::protobuf::Descriptor* AuthenticateOk_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AuthenticateOk_reflection_ = NULL;
const ::google::protobuf::Descriptor* Reset_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Reset_reflection_ = NULL;
const ::google::protobuf::Descriptor* Close_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Close_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_mysqlx_5fsession_2eproto() {
  protobuf_AddDesc_mysqlx_5fsession_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "mysqlx_session.proto");
  GOOGLE_CHECK(file != NULL);
  AuthenticateStart_descriptor_ = file->message_type(0);
  static const int AuthenticateStart_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateStart, mech_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateStart, auth_data_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateStart, initial_response_),
  };
  AuthenticateStart_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AuthenticateStart_descriptor_,
      AuthenticateStart::default_instance_,
      AuthenticateStart_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateStart, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateStart, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AuthenticateStart));
  AuthenticateContinue_descriptor_ = file->message_type(1);
  static const int AuthenticateContinue_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateContinue, auth_data_),
  };
  AuthenticateContinue_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AuthenticateContinue_descriptor_,
      AuthenticateContinue::default_instance_,
      AuthenticateContinue_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateContinue, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateContinue, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AuthenticateContinue));
  AuthenticateOk_descriptor_ = file->message_type(2);
  static const int AuthenticateOk_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateOk, auth_data_),
  };
  AuthenticateOk_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AuthenticateOk_descriptor_,
      AuthenticateOk::default_instance_,
      AuthenticateOk_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateOk, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateOk, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AuthenticateOk));
  Reset_descriptor_ = file->message_type(3);
  static const int Reset_offsets_[1] = {
  };
  Reset_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Reset_descriptor_,
      Reset::default_instance_,
      Reset_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reset, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reset, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Reset));
  Close_descriptor_ = file->message_type(4);
  static const int Close_offsets_[1] = {
  };
  Close_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Close_descriptor_,
      Close::default_instance_,
      Close_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Close, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Close, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Close));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_mysqlx_5fsession_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AuthenticateStart_descriptor_, &AuthenticateStart::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AuthenticateContinue_descriptor_, &AuthenticateContinue::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AuthenticateOk_descriptor_, &AuthenticateOk::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Reset_descriptor_, &Reset::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Close_descriptor_, &Close::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_mysqlx_5fsession_2eproto() {
  delete AuthenticateStart::default_instance_;
  delete AuthenticateStart_reflection_;
  delete AuthenticateContinue::default_instance_;
  delete AuthenticateContinue_reflection_;
  delete AuthenticateOk::default_instance_;
  delete AuthenticateOk_reflection_;
  delete Reset::default_instance_;
  delete Reset_reflection_;
  delete Close::default_instance_;
  delete Close_reflection_;
}

void protobuf_AddDesc_mysqlx_5fsession_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024mysqlx_session.proto\022\016Mysqlx.Session\"S"
    "\n\021AuthenticateStart\022\021\n\tmech_name\030\001 \002(\t\022\021"
    "\n\tauth_data\030\002 \001(\014\022\030\n\020initial_response\030\003 "
    "\001(\014\")\n\024AuthenticateContinue\022\021\n\tauth_data"
    "\030\001 \002(\014\"#\n\016AuthenticateOk\022\021\n\tauth_data\030\001 "
    "\001(\014\"\007\n\005Reset\"\007\n\005CloseB\036\n\034com.mysql.cj.my"
    "sqlx.protobuf", 253);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "mysqlx_session.proto", &protobuf_RegisterTypes);
  AuthenticateStart::default_instance_ = new AuthenticateStart();
  AuthenticateContinue::default_instance_ = new AuthenticateContinue();
  AuthenticateOk::default_instance_ = new AuthenticateOk();
  Reset::default_instance_ = new Reset();
  Close::default_instance_ = new Close();
  AuthenticateStart::default_instance_->InitAsDefaultInstance();
  AuthenticateContinue::default_instance_->InitAsDefaultInstance();
  AuthenticateOk::default_instance_->InitAsDefaultInstance();
  Reset::default_instance_->InitAsDefaultInstance();
  Close::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_mysqlx_5fsession_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_mysqlx_5fsession_2eproto {
  StaticDescriptorInitializer_mysqlx_5fsession_2eproto() {
    protobuf_AddDesc_mysqlx_5fsession_2eproto();
  }
} static_descriptor_initializer_mysqlx_5fsession_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int AuthenticateStart::kMechNameFieldNumber;
const int AuthenticateStart::kAuthDataFieldNumber;
const int AuthenticateStart::kInitialResponseFieldNumber;
#endif  // !_MSC_VER

AuthenticateStart::AuthenticateStart()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AuthenticateStart::InitAsDefaultInstance() {
}

AuthenticateStart::AuthenticateStart(const AuthenticateStart& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AuthenticateStart::SharedCtor() {
  _cached_size_ = 0;
  mech_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  auth_data_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  initial_response_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AuthenticateStart::~AuthenticateStart() {
  SharedDtor();
}

void AuthenticateStart::SharedDtor() {
  if (mech_name_ != &::google::protobuf::internal::kEmptyString) {
    delete mech_name_;
  }
  if (auth_data_ != &::google::protobuf::internal::kEmptyString) {
    delete auth_data_;
  }
  if (initial_response_ != &::google::protobuf::internal::kEmptyString) {
    delete initial_response_;
  }
  if (this != default_instance_) {
  }
}

void AuthenticateStart::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AuthenticateStart::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AuthenticateStart_descriptor_;
}

const AuthenticateStart& AuthenticateStart::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_mysqlx_5fsession_2eproto();
  return *default_instance_;
}

AuthenticateStart* AuthenticateStart::default_instance_ = NULL;

AuthenticateStart* AuthenticateStart::New() const {
  return new AuthenticateStart;
}

void AuthenticateStart::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_mech_name()) {
      if (mech_name_ != &::google::protobuf::internal::kEmptyString) {
        mech_name_->clear();
      }
    }
    if (has_auth_data()) {
      if (auth_data_ != &::google::protobuf::internal::kEmptyString) {
        auth_data_->clear();
      }
    }
    if (has_initial_response()) {
      if (initial_response_ != &::google::protobuf::internal::kEmptyString) {
        initial_response_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AuthenticateStart::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string mech_name = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_mech_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->mech_name().data(), this->mech_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_auth_data;
        break;
      }

      // optional bytes auth_data = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_auth_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_auth_data()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_initial_response;
        break;
      }

      // optional bytes initial_response = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_initial_response:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_initial_response()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void AuthenticateStart::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string mech_name = 1;
  if (has_mech_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->mech_name().data(), this->mech_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->mech_name(), output);
  }

  // optional bytes auth_data = 2;
  if (has_auth_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      2, this->auth_data(), output);
  }

  // optional bytes initial_response = 3;
  if (has_initial_response()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      3, this->initial_response(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AuthenticateStart::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string mech_name = 1;
  if (has_mech_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->mech_name().data(), this->mech_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->mech_name(), target);
  }

  // optional bytes auth_data = 2;
  if (has_auth_data()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->auth_data(), target);
  }

  // optional bytes initial_response = 3;
  if (has_initial_response()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->initial_response(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AuthenticateStart::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string mech_name = 1;
    if (has_mech_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->mech_name());
    }

    // optional bytes auth_data = 2;
    if (has_auth_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->auth_data());
    }

    // optional bytes initial_response = 3;
    if (has_initial_response()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->initial_response());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void AuthenticateStart::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AuthenticateStart* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AuthenticateStart*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AuthenticateStart::MergeFrom(const AuthenticateStart& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_mech_name()) {
      set_mech_name(from.mech_name());
    }
    if (from.has_auth_data()) {
      set_auth_data(from.auth_data());
    }
    if (from.has_initial_response()) {
      set_initial_response(from.initial_response());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AuthenticateStart::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AuthenticateStart::CopyFrom(const AuthenticateStart& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AuthenticateStart::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void AuthenticateStart::Swap(AuthenticateStart* other) {
  if (other != this) {
    std::swap(mech_name_, other->mech_name_);
    std::swap(auth_data_, other->auth_data_);
    std::swap(initial_response_, other->initial_response_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AuthenticateStart::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AuthenticateStart_descriptor_;
  metadata.reflection = AuthenticateStart_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AuthenticateContinue::kAuthDataFieldNumber;
#endif  // !_MSC_VER

AuthenticateContinue::AuthenticateContinue()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AuthenticateContinue::InitAsDefaultInstance() {
}

AuthenticateContinue::AuthenticateContinue(const AuthenticateContinue& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AuthenticateContinue::SharedCtor() {
  _cached_size_ = 0;
  auth_data_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AuthenticateContinue::~AuthenticateContinue() {
  SharedDtor();
}

void AuthenticateContinue::SharedDtor() {
  if (auth_data_ != &::google::protobuf::internal::kEmptyString) {
    delete auth_data_;
  }
  if (this != default_instance_) {
  }
}

void AuthenticateContinue::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AuthenticateContinue::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AuthenticateContinue_descriptor_;
}

const AuthenticateContinue& AuthenticateContinue::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_mysqlx_5fsession_2eproto();
  return *default_instance_;
}

AuthenticateContinue* AuthenticateContinue::default_instance_ = NULL;

AuthenticateContinue* AuthenticateContinue::New() const {
  return new AuthenticateContinue;
}

void AuthenticateContinue::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_auth_data()) {
      if (auth_data_ != &::google::protobuf::internal::kEmptyString) {
        auth_data_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AuthenticateContinue::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required bytes auth_data = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_auth_data()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void AuthenticateContinue::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required bytes auth_data = 1;
  if (has_auth_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      1, this->auth_data(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AuthenticateContinue::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required bytes auth_data = 1;
  if (has_auth_data()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        1, this->auth_data(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AuthenticateContinue::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required bytes auth_data = 1;
    if (has_auth_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->auth_data());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void AuthenticateContinue::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AuthenticateContinue* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AuthenticateContinue*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AuthenticateContinue::MergeFrom(const AuthenticateContinue& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_auth_data()) {
      set_auth_data(from.auth_data());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AuthenticateContinue::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AuthenticateContinue::CopyFrom(const AuthenticateContinue& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AuthenticateContinue::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void AuthenticateContinue::Swap(AuthenticateContinue* other) {
  if (other != this) {
    std::swap(auth_data_, other->auth_data_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AuthenticateContinue::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AuthenticateContinue_descriptor_;
  metadata.reflection = AuthenticateContinue_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AuthenticateOk::kAuthDataFieldNumber;
#endif  // !_MSC_VER

AuthenticateOk::AuthenticateOk()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AuthenticateOk::InitAsDefaultInstance() {
}

AuthenticateOk::AuthenticateOk(const AuthenticateOk& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AuthenticateOk::SharedCtor() {
  _cached_size_ = 0;
  auth_data_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AuthenticateOk::~AuthenticateOk() {
  SharedDtor();
}

void AuthenticateOk::SharedDtor() {
  if (auth_data_ != &::google::protobuf::internal::kEmptyString) {
    delete auth_data_;
  }
  if (this != default_instance_) {
  }
}

void AuthenticateOk::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AuthenticateOk::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AuthenticateOk_descriptor_;
}

const AuthenticateOk& AuthenticateOk::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_mysqlx_5fsession_2eproto();
  return *default_instance_;
}

AuthenticateOk* AuthenticateOk::default_instance_ = NULL;

AuthenticateOk* AuthenticateOk::New() const {
  return new AuthenticateOk;
}

void AuthenticateOk::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_auth_data()) {
      if (auth_data_ != &::google::protobuf::internal::kEmptyString) {
        auth_data_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AuthenticateOk::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional bytes auth_data = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_auth_data()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void AuthenticateOk::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional bytes auth_data = 1;
  if (has_auth_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      1, this->auth_data(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AuthenticateOk::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional bytes auth_data = 1;
  if (has_auth_data()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        1, this->auth_data(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AuthenticateOk::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional bytes auth_data = 1;
    if (has_auth_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->auth_data());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void AuthenticateOk::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AuthenticateOk* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AuthenticateOk*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AuthenticateOk::MergeFrom(const AuthenticateOk& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_auth_data()) {
      set_auth_data(from.auth_data());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AuthenticateOk::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AuthenticateOk::CopyFrom(const AuthenticateOk& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AuthenticateOk::IsInitialized() const {

  return true;
}

void AuthenticateOk::Swap(AuthenticateOk* other) {
  if (other != this) {
    std::swap(auth_data_, other->auth_data_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AuthenticateOk::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AuthenticateOk_descriptor_;
  metadata.reflection = AuthenticateOk_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

Reset::Reset()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Reset::InitAsDefaultInstance() {
}

Reset::Reset(const Reset& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Reset::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Reset::~Reset() {
  SharedDtor();
}

void Reset::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Reset::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Reset::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Reset_descriptor_;
}

const Reset& Reset::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_mysqlx_5fsession_2eproto();
  return *default_instance_;
}

Reset* Reset::default_instance_ = NULL;

Reset* Reset::New() const {
  return new Reset;
}

void Reset::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Reset::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      return true;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
  return true;
#undef DO_
}

void Reset::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Reset::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Reset::ByteSize() const {
  int total_size = 0;

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Reset::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Reset* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Reset*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Reset::MergeFrom(const Reset& from) {
  GOOGLE_CHECK_NE(&from, this);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Reset::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Reset::CopyFrom(const Reset& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Reset::IsInitialized() const {

  return true;
}

void Reset::Swap(Reset* other) {
  if (other != this) {
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Reset::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Reset_descriptor_;
  metadata.reflection = Reset_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

Close::Close()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Close::InitAsDefaultInstance() {
}

Close::Close(const Close& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Close::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Close::~Close() {
  SharedDtor();
}

void Close::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Close::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Close::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Close_descriptor_;
}

const Close& Close::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_mysqlx_5fsession_2eproto();
  return *default_instance_;
}

Close* Close::default_instance_ = NULL;

Close* Close::New() const {
  return new Close;
}

void Close::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Close::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      return true;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
  return true;
#undef DO_
}

void Close::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Close::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Close::ByteSize() const {
  int total_size = 0;

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Close::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Close* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Close*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Close::MergeFrom(const Close& from) {
  GOOGLE_CHECK_NE(&from, this);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Close::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Close::CopyFrom(const Close& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Close::IsInitialized() const {

  return true;
}

void Close::Swap(Close* other) {
  if (other != this) {
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Close::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Close_descriptor_;
  metadata.reflection = Close_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Session
}  // namespace Mysqlx

// @@protoc_insertion_point(global_scope)
