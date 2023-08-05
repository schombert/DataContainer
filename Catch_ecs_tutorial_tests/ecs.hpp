#pragma once

//
// This file was automatically generated from: ecs.txt
// EDIT AT YOUR OWN RISK; all changes will be lost upon regeneration
// NOT SUITABLE FOR USE IN CRITICAL SOFTWARE WHERE LIVES OR LIVELIHOODS DEPEND ON THE CORRECT OPERATION
//

#include <cstdint>
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <array>
#include <memory>
#include <assert.h>
#include <cstring>
#include "common_types.hpp"
#ifndef DCON_NO_VE
#include "ve.hpp"
#endif

#ifdef NDEBUG
#ifdef _MSC_VER
#define DCON_RELEASE_INLINE __forceinline
#else
#define DCON_RELEASE_INLINE inline __attribute__((always_inline))
#endif
#else
#define DCON_RELEASE_INLINE inline
#endif
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4324 )
#endif

namespace dcon {
	struct load_record {
		bool entity : 1;
		bool entity__index : 1;
		bool entity_position_component : 1;
		bool entity_sprite_component : 1;
		bool position : 1;
		bool position__index : 1;
		bool position_x : 1;
		bool position_y : 1;
		bool position_rotation : 1;
		bool sprite : 1;
		bool sprite__index : 1;
		bool sprite_sprite_id : 1;
		load_record() {
			entity = false;
			entity__index = false;
			entity_position_component = false;
			entity_sprite_component = false;
			position = false;
			position__index = false;
			position_x = false;
			position_y = false;
			position_rotation = false;
			sprite = false;
			sprite__index = false;
			sprite_sprite_id = false;
		}
	};
	//
	// definition of strongly typed index for entity_id
	//
	class entity_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr entity_id() noexcept = default;
		explicit constexpr entity_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr entity_id(entity_id const& v) noexcept = default;
		constexpr entity_id(entity_id&& v) noexcept = default;
		
		entity_id& operator=(entity_id const& v) noexcept = default;
		entity_id& operator=(entity_id&& v) noexcept = default;
		constexpr bool operator==(entity_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(entity_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class entity_id_pair {
		public:
		entity_id left;
		entity_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(entity_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for position_id
	//
	class position_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr position_id() noexcept = default;
		explicit constexpr position_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr position_id(position_id const& v) noexcept = default;
		constexpr position_id(position_id&& v) noexcept = default;
		
		position_id& operator=(position_id const& v) noexcept = default;
		position_id& operator=(position_id&& v) noexcept = default;
		constexpr bool operator==(position_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(position_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class position_id_pair {
		public:
		position_id left;
		position_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(position_id id) { return bool(id); }
	
	//
	// definition of strongly typed index for sprite_id
	//
	class sprite_id {
		public:
		using value_base_t = uint16_t;
		using zero_is_null_t = std::true_type;
		
		uint16_t value = 0;
		
		constexpr sprite_id() noexcept = default;
		explicit constexpr sprite_id(uint16_t v) noexcept : value(v + 1) {}
		constexpr sprite_id(sprite_id const& v) noexcept = default;
		constexpr sprite_id(sprite_id&& v) noexcept = default;
		
		sprite_id& operator=(sprite_id const& v) noexcept = default;
		sprite_id& operator=(sprite_id&& v) noexcept = default;
		constexpr bool operator==(sprite_id v) const noexcept { return value == v.value; }
		constexpr bool operator!=(sprite_id v) const noexcept { return value != v.value; }
		explicit constexpr operator bool() const noexcept { return value != uint16_t(0); }
		constexpr DCON_RELEASE_INLINE int32_t index() const noexcept {
			return int32_t(value) - 1;
		}
	};
	
	class sprite_id_pair {
		public:
		sprite_id left;
		sprite_id right;
	};
	
	DCON_RELEASE_INLINE bool is_valid_index(sprite_id id) { return bool(id); }
	
}

#ifndef DCON_NO_VE
namespace ve {
	template<>
	struct value_to_vector_type_s<dcon::entity_id> {
		using type = ::ve::tagged_vector<dcon::entity_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::position_id> {
		using type = ::ve::tagged_vector<dcon::position_id>;
	};
	
	template<>
	struct value_to_vector_type_s<dcon::sprite_id> {
		using type = ::ve::tagged_vector<dcon::sprite_id>;
	};
	
}

#endif
namespace dcon {
	namespace detail {
	}

	class data_container;

	namespace internal {
		class query_sprites_with_position_iterator;
		class query_sprites_with_position_const_iterator;
		class query_sprites_with_position_instance {
			public:
			data_container& container;
			query_sprites_with_position_instance(data_container& c ) : container(c)  {}
			query_sprites_with_position_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		class query_sprites_with_position_const_instance {
			public:
			data_container const& container;
			query_sprites_with_position_const_instance(data_container const& c ) : container(c)  {}
			query_sprites_with_position_const_iterator begin();
			dcon::invalid_iterator_type end() const {
				return dcon::invalid_iterator_type{};
			}
		};
		
		class const_object_iterator_entity;
		class object_iterator_entity;

		class alignas(64) entity_class {
			friend const_object_iterator_entity;
			friend object_iterator_entity;
			private:
			//
			// storage space for _index of type entity_id
			//
			struct dtype__index {
				entity_id values[3000];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 3000); }
			}
			m__index;
			
			//
			// storage space for position_component of type position_id
			//
			struct alignas(64) dtype_position_component {
				uint8_t padding[(63 + sizeof(position_id)) & ~uint64_t(63)];
				position_id values[(sizeof(position_id) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(position_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(position_id)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_position_component() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(position_id) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(position_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(position_id)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_position_component;
			
			//
			// storage space for link_back_position_component of type entity_id
			//
			struct alignas(64) dtype_link_back_position_component {
				uint8_t padding[(63 + sizeof(entity_id)) & ~uint64_t(63)];
				entity_id values[(sizeof(entity_id) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(entity_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(entity_id)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_link_back_position_component() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(entity_id) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(entity_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(entity_id)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_link_back_position_component;
			
			//
			// storage space for sprite_component of type sprite_id
			//
			struct alignas(64) dtype_sprite_component {
				uint8_t padding[(63 + sizeof(sprite_id)) & ~uint64_t(63)];
				sprite_id values[(sizeof(sprite_id) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(sprite_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(sprite_id)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_sprite_component() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(sprite_id) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(sprite_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(sprite_id)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_sprite_component;
			
			//
			// storage space for link_back_sprite_component of type entity_id
			//
			struct alignas(64) dtype_link_back_sprite_component {
				uint8_t padding[(63 + sizeof(entity_id)) & ~uint64_t(63)];
				entity_id values[(sizeof(entity_id) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(entity_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(entity_id)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_link_back_sprite_component() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(entity_id) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(entity_id))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(entity_id)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_link_back_sprite_component;
			
			entity_id first_free = entity_id();
			uint32_t size_used = 0;


			public:
			entity_class() {
				for(int32_t i = 3000 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = entity_id(uint16_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_position;
		class object_iterator_position;

		class alignas(64) position_class {
			friend const_object_iterator_position;
			friend object_iterator_position;
			private:
			//
			// storage space for _index of type position_id
			//
			struct dtype__index {
				position_id values[3000];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 3000); }
			}
			m__index;
			
			//
			// storage space for x of type float
			//
			struct alignas(64) dtype_x {
				uint8_t padding[(63 + sizeof(float)) & ~uint64_t(63)];
				float values[(sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_x() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_x;
			
			//
			// storage space for y of type float
			//
			struct alignas(64) dtype_y {
				uint8_t padding[(63 + sizeof(float)) & ~uint64_t(63)];
				float values[(sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_y() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_y;
			
			//
			// storage space for rotation of type float
			//
			struct alignas(64) dtype_rotation {
				uint8_t padding[(63 + sizeof(float)) & ~uint64_t(63)];
				float values[(sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_rotation() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(float) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(float))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(float)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_rotation;
			
			position_id first_free = position_id();
			uint32_t size_used = 0;


			public:
			position_class() {
				for(int32_t i = 3000 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = position_id(uint16_t(i));
				}
			}
			friend data_container;
		};

		class const_object_iterator_sprite;
		class object_iterator_sprite;

		class alignas(64) sprite_class {
			friend const_object_iterator_sprite;
			friend object_iterator_sprite;
			private:
			//
			// storage space for _index of type sprite_id
			//
			struct dtype__index {
				sprite_id values[3000];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype__index() { std::uninitialized_value_construct_n(values, 3000); }
			}
			m__index;
			
			//
			// storage space for sprite_id of type uint16_t
			//
			struct alignas(64) dtype_sprite_id {
				uint8_t padding[(63 + sizeof(uint16_t)) & ~uint64_t(63)];
				uint16_t values[(sizeof(uint16_t) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(uint16_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(uint16_t)) - uint32_t(1)) : uint32_t(3000))];
				DCON_RELEASE_INLINE auto vptr() const { return values; }
				DCON_RELEASE_INLINE auto vptr() { return values; }
				dtype_sprite_id() { std::uninitialized_value_construct_n(values - 1, 1 + (sizeof(uint16_t) <= 64 ? (uint32_t(3000) + (uint32_t(64) / uint32_t(sizeof(uint16_t))) - uint32_t(1)) & ~(uint32_t(64) / uint32_t(sizeof(uint16_t)) - uint32_t(1)) : uint32_t(3000))); }
			}
			m_sprite_id;
			
			sprite_id first_free = sprite_id();
			uint32_t size_used = 0;


			public:
			sprite_class() {
				for(int32_t i = 3000 - 1; i >= 0; --i) {
					m__index.vptr()[i] = first_free;
					first_free = sprite_id(uint16_t(i));
				}
			}
			friend data_container;
		};

	}

	class entity_const_fat_id;
	class entity_fat_id;
	class position_const_fat_id;
	class position_fat_id;
	class sprite_const_fat_id;
	class sprite_fat_id;
	class entity_fat_id {
		friend data_container;
		public:
		data_container& container;
		entity_id id;
		entity_fat_id(data_container& c, entity_id i) noexcept : container(c), id(i) {}
		entity_fat_id(entity_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator entity_id() const noexcept { return id; }
		DCON_RELEASE_INLINE entity_fat_id& operator=(entity_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE entity_fat_id& operator=(entity_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(entity_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(entity_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(entity_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(entity_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE position_fat_id get_position_component() const noexcept;
		DCON_RELEASE_INLINE void set_position_component(position_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_position_component(position_id val) const noexcept;
		DCON_RELEASE_INLINE sprite_fat_id get_sprite_component() const noexcept;
		DCON_RELEASE_INLINE void set_sprite_component(sprite_id val) const noexcept;
		DCON_RELEASE_INLINE bool try_set_sprite_component(sprite_id val) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE entity_fat_id fatten(data_container& c, entity_id id) noexcept {
		return entity_fat_id(c, id);
	}
	
	class entity_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		entity_id id;
		entity_const_fat_id(data_container const& c, entity_id i) noexcept : container(c), id(i) {}
		entity_const_fat_id(entity_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		entity_const_fat_id(entity_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator entity_id() const noexcept { return id; }
		DCON_RELEASE_INLINE entity_const_fat_id& operator=(entity_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE entity_const_fat_id& operator=(entity_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE entity_const_fat_id& operator=(entity_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(entity_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(entity_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(entity_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(entity_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(entity_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(entity_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE position_const_fat_id get_position_component() const noexcept;
		DCON_RELEASE_INLINE sprite_const_fat_id get_sprite_component() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(entity_fat_id const& l, entity_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(entity_fat_id const& l, entity_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE entity_const_fat_id fatten(data_container const& c, entity_id id) noexcept {
		return entity_const_fat_id(c, id);
	}
	
	class position_fat_id {
		friend data_container;
		public:
		data_container& container;
		position_id id;
		position_fat_id(data_container& c, position_id i) noexcept : container(c), id(i) {}
		position_fat_id(position_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator position_id() const noexcept { return id; }
		DCON_RELEASE_INLINE position_fat_id& operator=(position_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE position_fat_id& operator=(position_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(position_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(position_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(position_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(position_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE float& get_x() const noexcept;
		DCON_RELEASE_INLINE void set_x(float v) const noexcept;
		DCON_RELEASE_INLINE float& get_y() const noexcept;
		DCON_RELEASE_INLINE void set_y(float v) const noexcept;
		DCON_RELEASE_INLINE float& get_rotation() const noexcept;
		DCON_RELEASE_INLINE void set_rotation(float v) const noexcept;
		DCON_RELEASE_INLINE entity_fat_id get_entity_as_position_component() const noexcept;
		DCON_RELEASE_INLINE void remove_entity_as_position_component() const noexcept;
		DCON_RELEASE_INLINE entity_fat_id get_entity() const noexcept;
		DCON_RELEASE_INLINE void remove_entity() const noexcept;
		DCON_RELEASE_INLINE sprite_fat_id get_sprite_component_from_entity() const noexcept;
		DCON_RELEASE_INLINE void set_sprite_component_from_entity(sprite_id v) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE position_fat_id fatten(data_container& c, position_id id) noexcept {
		return position_fat_id(c, id);
	}
	
	class position_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		position_id id;
		position_const_fat_id(data_container const& c, position_id i) noexcept : container(c), id(i) {}
		position_const_fat_id(position_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		position_const_fat_id(position_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator position_id() const noexcept { return id; }
		DCON_RELEASE_INLINE position_const_fat_id& operator=(position_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE position_const_fat_id& operator=(position_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE position_const_fat_id& operator=(position_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(position_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(position_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(position_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(position_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(position_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(position_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE float get_x() const noexcept;
		DCON_RELEASE_INLINE float get_y() const noexcept;
		DCON_RELEASE_INLINE float get_rotation() const noexcept;
		DCON_RELEASE_INLINE entity_const_fat_id get_entity_as_position_component() const noexcept;
		DCON_RELEASE_INLINE entity_const_fat_id get_entity() const noexcept;
		DCON_RELEASE_INLINE sprite_const_fat_id get_sprite_component_from_entity() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(position_fat_id const& l, position_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(position_fat_id const& l, position_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE position_const_fat_id fatten(data_container const& c, position_id id) noexcept {
		return position_const_fat_id(c, id);
	}
	
	class sprite_fat_id {
		friend data_container;
		public:
		data_container& container;
		sprite_id id;
		sprite_fat_id(data_container& c, sprite_id i) noexcept : container(c), id(i) {}
		sprite_fat_id(sprite_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator sprite_id() const noexcept { return id; }
		DCON_RELEASE_INLINE sprite_fat_id& operator=(sprite_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE sprite_fat_id& operator=(sprite_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(sprite_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(sprite_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(sprite_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(sprite_id other) const noexcept {
			return id != other;
		}
		explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE uint16_t& get_sprite_id() const noexcept;
		DCON_RELEASE_INLINE void set_sprite_id(uint16_t v) const noexcept;
		DCON_RELEASE_INLINE entity_fat_id get_entity_as_sprite_component() const noexcept;
		DCON_RELEASE_INLINE void remove_entity_as_sprite_component() const noexcept;
		DCON_RELEASE_INLINE entity_fat_id get_entity() const noexcept;
		DCON_RELEASE_INLINE void remove_entity() const noexcept;
		DCON_RELEASE_INLINE position_fat_id get_position_component_from_entity() const noexcept;
		DCON_RELEASE_INLINE void set_position_component_from_entity(position_id v) const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE sprite_fat_id fatten(data_container& c, sprite_id id) noexcept {
		return sprite_fat_id(c, id);
	}
	
	class sprite_const_fat_id {
		friend data_container;
		public:
		data_container const& container;
		sprite_id id;
		sprite_const_fat_id(data_container const& c, sprite_id i) noexcept : container(c), id(i) {}
		sprite_const_fat_id(sprite_const_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		sprite_const_fat_id(sprite_fat_id const& o) noexcept : container(o.container), id(o.id) {}
		DCON_RELEASE_INLINE operator sprite_id() const noexcept { return id; }
		DCON_RELEASE_INLINE sprite_const_fat_id& operator=(sprite_const_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE sprite_const_fat_id& operator=(sprite_fat_id const& other) noexcept {
			assert(&container == &other.container);
			id = other.id;
			return *this;
		}
		DCON_RELEASE_INLINE sprite_const_fat_id& operator=(sprite_id other) noexcept {
			id = other;
			return *this;
		}
		DCON_RELEASE_INLINE bool operator==(sprite_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(sprite_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id == other.id;
		}
		DCON_RELEASE_INLINE bool operator==(sprite_id other) const noexcept {
			return id == other;
		}
		DCON_RELEASE_INLINE bool operator!=(sprite_const_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(sprite_fat_id const& other) const noexcept {
			assert(&container == &other.container);
			return id != other.id;
		}
		DCON_RELEASE_INLINE bool operator!=(sprite_id other) const noexcept {
			return id != other;
		}
		DCON_RELEASE_INLINE explicit operator bool() const noexcept { return bool(id); }
		DCON_RELEASE_INLINE uint16_t get_sprite_id() const noexcept;
		DCON_RELEASE_INLINE entity_const_fat_id get_entity_as_sprite_component() const noexcept;
		DCON_RELEASE_INLINE entity_const_fat_id get_entity() const noexcept;
		DCON_RELEASE_INLINE position_const_fat_id get_position_component_from_entity() const noexcept;
		DCON_RELEASE_INLINE bool is_valid() const noexcept;
		
	};
	DCON_RELEASE_INLINE bool operator==(sprite_fat_id const& l, sprite_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id == other.id;
	}
	DCON_RELEASE_INLINE bool operator!=(sprite_fat_id const& l, sprite_const_fat_id const& other) noexcept {
		assert(&l.container == &other.container);
		return l.id != other.id;
	}
	DCON_RELEASE_INLINE sprite_const_fat_id fatten(data_container const& c, sprite_id id) noexcept {
		return sprite_const_fat_id(c, id);
	}
	
	namespace internal {
		class object_iterator_entity {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_entity(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_entity& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_entity& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_entity const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_entity const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE entity_fat_id operator*() const noexcept {
				return entity_fat_id(container, entity_id(entity_id::value_base_t(index)));
			}
		};
		class const_object_iterator_entity {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_entity(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_entity& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_entity& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_entity const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_entity const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE entity_const_fat_id operator*() const noexcept {
				return entity_const_fat_id(container, entity_id(entity_id::value_base_t(index)));
			}
		};
		
		class object_iterator_position {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_position(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_position& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_position& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_position const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_position const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE position_fat_id operator*() const noexcept {
				return position_fat_id(container, position_id(position_id::value_base_t(index)));
			}
		};
		class const_object_iterator_position {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_position(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_position& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_position& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_position const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_position const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE position_const_fat_id operator*() const noexcept {
				return position_const_fat_id(container, position_id(position_id::value_base_t(index)));
			}
		};
		
		class object_iterator_sprite {
			private:
			data_container& container;
			uint32_t index = 0;
			public:
			object_iterator_sprite(data_container& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE object_iterator_sprite& operator++() noexcept;
			DCON_RELEASE_INLINE object_iterator_sprite& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(object_iterator_sprite const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(object_iterator_sprite const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE sprite_fat_id operator*() const noexcept {
				return sprite_fat_id(container, sprite_id(sprite_id::value_base_t(index)));
			}
		};
		class const_object_iterator_sprite {
			private:
			data_container const& container;
			uint32_t index = 0;
			public:
			const_object_iterator_sprite(data_container const& c, uint32_t i) noexcept;
			DCON_RELEASE_INLINE const_object_iterator_sprite& operator++() noexcept;
			DCON_RELEASE_INLINE const_object_iterator_sprite& operator--() noexcept;
			DCON_RELEASE_INLINE bool operator==(const_object_iterator_sprite const& o) const noexcept {
				return &container == &o.container && index == o.index;
			}
			DCON_RELEASE_INLINE bool operator!=(const_object_iterator_sprite const& o) const noexcept {
				return !(*this == o);
			}
			DCON_RELEASE_INLINE sprite_const_fat_id operator*() const noexcept {
				return sprite_const_fat_id(container, sprite_id(sprite_id::value_base_t(index)));
			}
		};
		
	}

	class alignas(64) data_container {
		public:
		internal::entity_class entity;
		internal::position_class position;
		internal::sprite_class sprite;

		//
		// Functions for entity:
		//
		DCON_RELEASE_INLINE position_id entity_get_position_component(entity_id id) const noexcept {
			return entity.m_position_component.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<position_id> entity_get_position_component(ve::contiguous_tags<entity_id> id) const noexcept {
			return ve::load(id, entity.m_position_component.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<position_id> entity_get_position_component(ve::partial_contiguous_tags<entity_id> id) const noexcept {
			return ve::load(id, entity.m_position_component.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<position_id> entity_get_position_component(ve::tagged_vector<entity_id> id) const noexcept {
			return ve::load(id, entity.m_position_component.vptr());
		}
		#endif
		private:
		void internal_entity_set_position_component(entity_id id, position_id value) noexcept {
			if(auto old_value = entity.m_position_component.vptr()[id.index()]; bool(old_value)) {
				entity.m_link_back_position_component.vptr()[old_value.index()] = entity_id();
			}
			if(bool(value)) {
				if(auto old_rel = entity.m_link_back_position_component.vptr()[value.index()]; bool(old_rel)) {
					entity.m_position_component.vptr()[old_rel.index()] = position_id();
				}
				entity.m_link_back_position_component.vptr()[value.index()] = id;
			}
			entity.m_position_component.vptr()[id.index()] = value;
		}
		public:
		void entity_set_position_component(entity_id id, position_id value) noexcept {
			if(auto old_value = entity.m_position_component.vptr()[id.index()]; bool(old_value)) {
				entity.m_link_back_position_component.vptr()[old_value.index()] = entity_id();
			}
			if(bool(value)) {
				if(auto old_rel = entity.m_link_back_position_component.vptr()[value.index()]; bool(old_rel)) {
					entity.m_position_component.vptr()[old_rel.index()] = position_id();
				}
				entity.m_link_back_position_component.vptr()[value.index()] = id;
				entity.m_position_component.vptr()[id.index()] = value;
			} else {
				entity.m_position_component.vptr()[id.index()] = value;
			}
		}
		bool entity_try_set_position_component(entity_id id, position_id value) noexcept {
			if(bool(value)) {
				if(auto old_rel = entity.m_link_back_position_component.vptr()[value.index()]; bool(old_rel)) {
					return false;
				}
				entity.m_link_back_position_component.vptr()[value.index()] = id;
			}
			if(auto old_value = entity.m_position_component.vptr()[id.index()]; bool(old_value)) {
				entity.m_link_back_position_component.vptr()[old_value.index()] = entity_id();
			}
			entity.m_position_component.vptr()[id.index()] = value;
			return true;
		}
		DCON_RELEASE_INLINE sprite_id entity_get_sprite_component(entity_id id) const noexcept {
			return entity.m_sprite_component.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<sprite_id> entity_get_sprite_component(ve::contiguous_tags<entity_id> id) const noexcept {
			return ve::load(id, entity.m_sprite_component.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<sprite_id> entity_get_sprite_component(ve::partial_contiguous_tags<entity_id> id) const noexcept {
			return ve::load(id, entity.m_sprite_component.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<sprite_id> entity_get_sprite_component(ve::tagged_vector<entity_id> id) const noexcept {
			return ve::load(id, entity.m_sprite_component.vptr());
		}
		#endif
		private:
		void internal_entity_set_sprite_component(entity_id id, sprite_id value) noexcept {
			if(auto old_value = entity.m_sprite_component.vptr()[id.index()]; bool(old_value)) {
				entity.m_link_back_sprite_component.vptr()[old_value.index()] = entity_id();
			}
			if(bool(value)) {
				if(auto old_rel = entity.m_link_back_sprite_component.vptr()[value.index()]; bool(old_rel)) {
					entity.m_sprite_component.vptr()[old_rel.index()] = sprite_id();
				}
				entity.m_link_back_sprite_component.vptr()[value.index()] = id;
			}
			entity.m_sprite_component.vptr()[id.index()] = value;
		}
		public:
		void entity_set_sprite_component(entity_id id, sprite_id value) noexcept {
			if(auto old_value = entity.m_sprite_component.vptr()[id.index()]; bool(old_value)) {
				entity.m_link_back_sprite_component.vptr()[old_value.index()] = entity_id();
			}
			if(bool(value)) {
				if(auto old_rel = entity.m_link_back_sprite_component.vptr()[value.index()]; bool(old_rel)) {
					entity.m_sprite_component.vptr()[old_rel.index()] = sprite_id();
				}
				entity.m_link_back_sprite_component.vptr()[value.index()] = id;
				entity.m_sprite_component.vptr()[id.index()] = value;
			} else {
				entity.m_sprite_component.vptr()[id.index()] = value;
			}
		}
		bool entity_try_set_sprite_component(entity_id id, sprite_id value) noexcept {
			if(bool(value)) {
				if(auto old_rel = entity.m_link_back_sprite_component.vptr()[value.index()]; bool(old_rel)) {
					return false;
				}
				entity.m_link_back_sprite_component.vptr()[value.index()] = id;
			}
			if(auto old_value = entity.m_sprite_component.vptr()[id.index()]; bool(old_value)) {
				entity.m_link_back_sprite_component.vptr()[old_value.index()] = entity_id();
			}
			entity.m_sprite_component.vptr()[id.index()] = value;
			return true;
		}
		DCON_RELEASE_INLINE bool entity_is_valid(entity_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < entity.size_used && entity.m__index.vptr()[id.index()] == id;
		}
		
		void on_delete_entity(entity_id id);
		uint32_t entity_size() const noexcept { return entity.size_used; }

		//
		// Functions for position:
		//
		//
		// accessors for position: x
		//
		DCON_RELEASE_INLINE float const& position_get_x(position_id id) const noexcept {
			return position.m_x.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE float& position_get_x(position_id id) noexcept {
			return position.m_x.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> position_get_x(ve::contiguous_tags<position_id> id) const noexcept {
			return ve::load(id, position.m_x.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> position_get_x(ve::partial_contiguous_tags<position_id> id) const noexcept {
			return ve::load(id, position.m_x.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> position_get_x(ve::tagged_vector<position_id> id) const noexcept {
			return ve::load(id, position.m_x.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void position_set_x(position_id id, float value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
			position.m_x.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void position_set_x(ve::contiguous_tags<position_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, position.m_x.vptr(), values);
		}
		DCON_RELEASE_INLINE void position_set_x(ve::partial_contiguous_tags<position_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, position.m_x.vptr(), values);
		}
		DCON_RELEASE_INLINE void position_set_x(ve::tagged_vector<position_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, position.m_x.vptr(), values);
		}
		#endif
		//
		// accessors for position: y
		//
		DCON_RELEASE_INLINE float const& position_get_y(position_id id) const noexcept {
			return position.m_y.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE float& position_get_y(position_id id) noexcept {
			return position.m_y.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> position_get_y(ve::contiguous_tags<position_id> id) const noexcept {
			return ve::load(id, position.m_y.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> position_get_y(ve::partial_contiguous_tags<position_id> id) const noexcept {
			return ve::load(id, position.m_y.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> position_get_y(ve::tagged_vector<position_id> id) const noexcept {
			return ve::load(id, position.m_y.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void position_set_y(position_id id, float value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
			position.m_y.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void position_set_y(ve::contiguous_tags<position_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, position.m_y.vptr(), values);
		}
		DCON_RELEASE_INLINE void position_set_y(ve::partial_contiguous_tags<position_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, position.m_y.vptr(), values);
		}
		DCON_RELEASE_INLINE void position_set_y(ve::tagged_vector<position_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, position.m_y.vptr(), values);
		}
		#endif
		//
		// accessors for position: rotation
		//
		DCON_RELEASE_INLINE float const& position_get_rotation(position_id id) const noexcept {
			return position.m_rotation.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE float& position_get_rotation(position_id id) noexcept {
			return position.m_rotation.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> position_get_rotation(ve::contiguous_tags<position_id> id) const noexcept {
			return ve::load(id, position.m_rotation.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> position_get_rotation(ve::partial_contiguous_tags<position_id> id) const noexcept {
			return ve::load(id, position.m_rotation.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<float> position_get_rotation(ve::tagged_vector<position_id> id) const noexcept {
			return ve::load(id, position.m_rotation.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void position_set_rotation(position_id id, float value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
			position.m_rotation.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void position_set_rotation(ve::contiguous_tags<position_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, position.m_rotation.vptr(), values);
		}
		DCON_RELEASE_INLINE void position_set_rotation(ve::partial_contiguous_tags<position_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, position.m_rotation.vptr(), values);
		}
		DCON_RELEASE_INLINE void position_set_rotation(ve::tagged_vector<position_id> id, ve::value_to_vector_type<float> values) noexcept {
			ve::store(id, position.m_rotation.vptr(), values);
		}
		#endif
		DCON_RELEASE_INLINE entity_id position_get_entity_as_position_component(position_id id) const noexcept {
			return entity.m_link_back_position_component.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> position_get_entity_as_position_component(ve::contiguous_tags<position_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_position_component.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> position_get_entity_as_position_component(ve::partial_contiguous_tags<position_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_position_component.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> position_get_entity_as_position_component(ve::tagged_vector<position_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_position_component.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void position_remove_entity_as_position_component(position_id id) noexcept {
			if(auto backid = entity.m_link_back_position_component.vptr()[id.index()]; bool(backid)) {
				entity_set_position_component(backid, position_id());
			}
		}
		DCON_RELEASE_INLINE entity_id position_get_entity(position_id id) const noexcept {
			return entity.m_link_back_position_component.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> position_get_entity(ve::contiguous_tags<position_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_position_component.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> position_get_entity(ve::partial_contiguous_tags<position_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_position_component.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> position_get_entity(ve::tagged_vector<position_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_position_component.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void position_remove_entity(position_id id) noexcept {
			if(auto backid = entity.m_link_back_position_component.vptr()[id.index()]; bool(backid)) {
				entity_set_position_component(backid, position_id());
			}
		}
		sprite_id position_get_sprite_component_from_entity(position_id id) const {
			return entity_get_sprite_component(entity.m_link_back_position_component.vptr()[id.index()]);
		}
		#ifndef DCON_NO_VE
		ve::value_to_vector_type<sprite_id> position_get_sprite_component_from_entity(ve::contiguous_tags<position_id> id) const {
			auto ref_id = ve::load(id, entity.m_link_back_position_component.vptr());
			return entity_get_sprite_component(ref_id);
		}
		ve::value_to_vector_type<sprite_id> position_get_sprite_component_from_entity(ve::partial_contiguous_tags<position_id> id) const {
			auto ref_id = ve::load(id, entity.m_link_back_position_component.vptr());
			return entity_get_sprite_component(ref_id);
		}
		ve::value_to_vector_type<sprite_id> position_get_sprite_component_from_entity(ve::tagged_vector<position_id> id) const {
			auto ref_id = ve::load(id, entity.m_link_back_position_component.vptr());
			return entity_get_sprite_component(ref_id);
		}
		#endif
		void position_set_sprite_component_from_entity(position_id id, sprite_id val) {
			if(auto ref_id = entity.m_link_back_position_component.vptr()[id.index()]; bool(ref_id)) {
				entity_set_sprite_component(ref_id, val);
			}
		}
		DCON_RELEASE_INLINE bool position_is_valid(position_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < position.size_used && position.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t position_size() const noexcept { return position.size_used; }

		//
		// Functions for sprite:
		//
		//
		// accessors for sprite: sprite_id
		//
		DCON_RELEASE_INLINE uint16_t const& sprite_get_sprite_id(sprite_id id) const noexcept {
			return sprite.m_sprite_id.vptr()[id.index()];
		}
		DCON_RELEASE_INLINE uint16_t& sprite_get_sprite_id(sprite_id id) noexcept {
			return sprite.m_sprite_id.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::value_to_vector_type<uint16_t> sprite_get_sprite_id(ve::contiguous_tags<sprite_id> id) const noexcept {
			return ve::load(id, sprite.m_sprite_id.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<uint16_t> sprite_get_sprite_id(ve::partial_contiguous_tags<sprite_id> id) const noexcept {
			return ve::load(id, sprite.m_sprite_id.vptr());
		}
		DCON_RELEASE_INLINE ve::value_to_vector_type<uint16_t> sprite_get_sprite_id(ve::tagged_vector<sprite_id> id) const noexcept {
			return ve::load(id, sprite.m_sprite_id.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void sprite_set_sprite_id(sprite_id id, uint16_t value) noexcept {
			#ifdef DCON_TRAP_INVALID_STORE
			assert(id.index() >= 0);
			#endif
			sprite.m_sprite_id.vptr()[id.index()] = value;
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE void sprite_set_sprite_id(ve::contiguous_tags<sprite_id> id, ve::value_to_vector_type<uint16_t> values) noexcept {
			ve::store(id, sprite.m_sprite_id.vptr(), values);
		}
		DCON_RELEASE_INLINE void sprite_set_sprite_id(ve::partial_contiguous_tags<sprite_id> id, ve::value_to_vector_type<uint16_t> values) noexcept {
			ve::store(id, sprite.m_sprite_id.vptr(), values);
		}
		DCON_RELEASE_INLINE void sprite_set_sprite_id(ve::tagged_vector<sprite_id> id, ve::value_to_vector_type<uint16_t> values) noexcept {
			ve::store(id, sprite.m_sprite_id.vptr(), values);
		}
		#endif
		DCON_RELEASE_INLINE entity_id sprite_get_entity_as_sprite_component(sprite_id id) const noexcept {
			return entity.m_link_back_sprite_component.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> sprite_get_entity_as_sprite_component(ve::contiguous_tags<sprite_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_sprite_component.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> sprite_get_entity_as_sprite_component(ve::partial_contiguous_tags<sprite_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_sprite_component.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> sprite_get_entity_as_sprite_component(ve::tagged_vector<sprite_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_sprite_component.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void sprite_remove_entity_as_sprite_component(sprite_id id) noexcept {
			if(auto backid = entity.m_link_back_sprite_component.vptr()[id.index()]; bool(backid)) {
				entity_set_sprite_component(backid, sprite_id());
			}
		}
		DCON_RELEASE_INLINE entity_id sprite_get_entity(sprite_id id) const noexcept {
			return entity.m_link_back_sprite_component.vptr()[id.index()];
		}
		#ifndef DCON_NO_VE
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> sprite_get_entity(ve::contiguous_tags<sprite_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_sprite_component.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> sprite_get_entity(ve::partial_contiguous_tags<sprite_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_sprite_component.vptr());
		}
		DCON_RELEASE_INLINE ve::tagged_vector<entity_id> sprite_get_entity(ve::tagged_vector<sprite_id> id) const noexcept {
			return ve::load(id, entity.m_link_back_sprite_component.vptr());
		}
		#endif
		DCON_RELEASE_INLINE void sprite_remove_entity(sprite_id id) noexcept {
			if(auto backid = entity.m_link_back_sprite_component.vptr()[id.index()]; bool(backid)) {
				entity_set_sprite_component(backid, sprite_id());
			}
		}
		position_id sprite_get_position_component_from_entity(sprite_id id) const {
			return entity_get_position_component(entity.m_link_back_sprite_component.vptr()[id.index()]);
		}
		#ifndef DCON_NO_VE
		ve::value_to_vector_type<position_id> sprite_get_position_component_from_entity(ve::contiguous_tags<sprite_id> id) const {
			auto ref_id = ve::load(id, entity.m_link_back_sprite_component.vptr());
			return entity_get_position_component(ref_id);
		}
		ve::value_to_vector_type<position_id> sprite_get_position_component_from_entity(ve::partial_contiguous_tags<sprite_id> id) const {
			auto ref_id = ve::load(id, entity.m_link_back_sprite_component.vptr());
			return entity_get_position_component(ref_id);
		}
		ve::value_to_vector_type<position_id> sprite_get_position_component_from_entity(ve::tagged_vector<sprite_id> id) const {
			auto ref_id = ve::load(id, entity.m_link_back_sprite_component.vptr());
			return entity_get_position_component(ref_id);
		}
		#endif
		void sprite_set_position_component_from_entity(sprite_id id, position_id val) {
			if(auto ref_id = entity.m_link_back_sprite_component.vptr()[id.index()]; bool(ref_id)) {
				entity_set_position_component(ref_id, val);
			}
		}
		DCON_RELEASE_INLINE bool sprite_is_valid(sprite_id id) const noexcept {
			return bool(id) && uint32_t(id.index()) < sprite.size_used && sprite.m__index.vptr()[id.index()] == id;
		}
		
		uint32_t sprite_size() const noexcept { return sprite.size_used; }


		//
		// container delete for entity
		//
		void delete_entity(entity_id id_removed) {
			if(!entity_is_valid(id_removed)) return;
			on_delete_entity(id_removed);
			entity.m__index.vptr()[id_removed.index()] = entity.first_free;
			entity.first_free = id_removed;
			if(int32_t(entity.size_used) - 1 == id_removed.index()) {
				for( ; entity.size_used > 0 && entity.m__index.vptr()[entity.size_used - 1] != entity_id(entity_id::value_base_t(entity.size_used - 1));  --entity.size_used) ;
			}
			internal_entity_set_position_component(id_removed, position_id());
			internal_entity_set_sprite_component(id_removed, sprite_id());
		}
		
		//
		// container resize for entity
		//
		void entity_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 3000) std::abort();
			#else
			if(new_size > 3000) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = entity.size_used;
			if(new_size < old_size) {
				entity.first_free = entity_id();
				int32_t i = int32_t(3000 - 1);
				for(; i >= int32_t(new_size); --i) {
					entity.m__index.vptr()[i] = entity.first_free;
					entity.first_free = entity_id(entity_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(entity.m__index.vptr()[i] != entity_id(entity_id::value_base_t(i))) {
						entity.m__index.vptr()[i] = entity.first_free;
						entity.first_free = entity_id(entity_id::value_base_t(i));
					}
				}
				std::fill_n(entity.m_position_component.vptr() + 0, old_size, position_id{});
				std::fill_n(entity.m_link_back_position_component.vptr() + 0, position.size_used, entity_id{});
				std::fill_n(entity.m_sprite_component.vptr() + 0, old_size, sprite_id{});
				std::fill_n(entity.m_link_back_sprite_component.vptr() + 0, sprite.size_used, entity_id{});
			} else if(new_size > old_size) {
				entity.first_free = entity_id();
				int32_t i = int32_t(3000 - 1);
				for(; i >= int32_t(old_size); --i) {
					entity.m__index.vptr()[i] = entity.first_free;
					entity.first_free = entity_id(entity_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(entity.m__index.vptr()[i] != entity_id(entity_id::value_base_t(i))) {
						entity.m__index.vptr()[i] = entity.first_free;
						entity.first_free = entity_id(entity_id::value_base_t(i));
					}
				}
			}
			entity.size_used = new_size;
		}
		
		//
		// container try create relationship for entity
		//
		entity_id try_create_entity(position_id position_component_p, sprite_id sprite_component_p) {
			if(bool(position_component_p) && bool(entity.m_link_back_position_component.vptr()[position_component_p.index()])) return entity_id();
			if(bool(sprite_component_p) && bool(entity.m_link_back_sprite_component.vptr()[sprite_component_p.index()])) return entity_id();
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(entity.first_free)) std::abort();
			#else
			if(!bool(entity.first_free)) throw dcon::out_of_space{};
			#endif
			entity_id new_id = entity.first_free;
			entity.first_free = entity.m__index.vptr()[entity.first_free.index()];
			entity.m__index.vptr()[new_id.index()] = new_id;
			entity.size_used = std::max(entity.size_used, uint32_t(new_id.index() + 1));
			internal_entity_set_position_component(new_id, position_component_p);
			internal_entity_set_sprite_component(new_id, sprite_component_p);
			return new_id;
		}
		
		//
		// container force create relationship for entity
		//
		entity_id force_create_entity(position_id position_component_p, sprite_id sprite_component_p) {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(entity.first_free)) std::abort();
			#else
			if(!bool(entity.first_free)) throw dcon::out_of_space{};
			#endif
			entity_id new_id = entity.first_free;
			entity.first_free = entity.m__index.vptr()[entity.first_free.index()];
			entity.m__index.vptr()[new_id.index()] = new_id;
			entity.size_used = std::max(entity.size_used, uint32_t(new_id.index() + 1));
			internal_entity_set_position_component(new_id, position_component_p);
			internal_entity_set_sprite_component(new_id, sprite_component_p);
			return new_id;
		}
		
		//
		// container delete for position
		//
		void delete_position(position_id id_removed) {
			if(!position_is_valid(id_removed)) return;
			position.m__index.vptr()[id_removed.index()] = position.first_free;
			position.first_free = id_removed;
			if(int32_t(position.size_used) - 1 == id_removed.index()) {
				for( ; position.size_used > 0 && position.m__index.vptr()[position.size_used - 1] != position_id(position_id::value_base_t(position.size_used - 1));  --position.size_used) ;
			}
			position_remove_entity_as_position_component(id_removed);
			position.m_x.vptr()[id_removed.index()] = float{};
			position.m_y.vptr()[id_removed.index()] = float{};
			position.m_rotation.vptr()[id_removed.index()] = float{};
		}
		
		//
		// container create for position
		//
		position_id create_position() {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(position.first_free)) std::abort();
			#else
			if(!bool(position.first_free)) throw dcon::out_of_space{};
			#endif
			position_id new_id = position.first_free;
			position.first_free = position.m__index.vptr()[position.first_free.index()];
			position.m__index.vptr()[new_id.index()] = new_id;
			position.size_used = std::max(position.size_used, uint32_t(new_id.index() + 1));
			return new_id;
		}
		
		//
		// container resize for position
		//
		void position_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 3000) std::abort();
			#else
			if(new_size > 3000) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = position.size_used;
			if(new_size < old_size) {
				position.first_free = position_id();
				int32_t i = int32_t(3000 - 1);
				for(; i >= int32_t(new_size); --i) {
					position.m__index.vptr()[i] = position.first_free;
					position.first_free = position_id(position_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(position.m__index.vptr()[i] != position_id(position_id::value_base_t(i))) {
						position.m__index.vptr()[i] = position.first_free;
						position.first_free = position_id(position_id::value_base_t(i));
					}
				}
				std::fill_n(position.m_x.vptr() + new_size, old_size - new_size, float{});
				std::fill_n(position.m_y.vptr() + new_size, old_size - new_size, float{});
				std::fill_n(position.m_rotation.vptr() + new_size, old_size - new_size, float{});
				entity_resize(0);
			} else if(new_size > old_size) {
				position.first_free = position_id();
				int32_t i = int32_t(3000 - 1);
				for(; i >= int32_t(old_size); --i) {
					position.m__index.vptr()[i] = position.first_free;
					position.first_free = position_id(position_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(position.m__index.vptr()[i] != position_id(position_id::value_base_t(i))) {
						position.m__index.vptr()[i] = position.first_free;
						position.first_free = position_id(position_id::value_base_t(i));
					}
				}
			}
			position.size_used = new_size;
		}
		
		//
		// container delete for sprite
		//
		void delete_sprite(sprite_id id_removed) {
			if(!sprite_is_valid(id_removed)) return;
			sprite.m__index.vptr()[id_removed.index()] = sprite.first_free;
			sprite.first_free = id_removed;
			if(int32_t(sprite.size_used) - 1 == id_removed.index()) {
				for( ; sprite.size_used > 0 && sprite.m__index.vptr()[sprite.size_used - 1] != sprite_id(sprite_id::value_base_t(sprite.size_used - 1));  --sprite.size_used) ;
			}
			sprite_remove_entity_as_sprite_component(id_removed);
			sprite.m_sprite_id.vptr()[id_removed.index()] = uint16_t{};
		}
		
		//
		// container create for sprite
		//
		sprite_id create_sprite() {
			#ifndef DCON_USE_EXCEPTIONS
			if(!bool(sprite.first_free)) std::abort();
			#else
			if(!bool(sprite.first_free)) throw dcon::out_of_space{};
			#endif
			sprite_id new_id = sprite.first_free;
			sprite.first_free = sprite.m__index.vptr()[sprite.first_free.index()];
			sprite.m__index.vptr()[new_id.index()] = new_id;
			sprite.size_used = std::max(sprite.size_used, uint32_t(new_id.index() + 1));
			return new_id;
		}
		
		//
		// container resize for sprite
		//
		void sprite_resize(uint32_t new_size) {
			#ifndef DCON_USE_EXCEPTIONS
			if(new_size > 3000) std::abort();
			#else
			if(new_size > 3000) throw dcon::out_of_space{};
			#endif
			const uint32_t old_size = sprite.size_used;
			if(new_size < old_size) {
				sprite.first_free = sprite_id();
				int32_t i = int32_t(3000 - 1);
				for(; i >= int32_t(new_size); --i) {
					sprite.m__index.vptr()[i] = sprite.first_free;
					sprite.first_free = sprite_id(sprite_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(sprite.m__index.vptr()[i] != sprite_id(sprite_id::value_base_t(i))) {
						sprite.m__index.vptr()[i] = sprite.first_free;
						sprite.first_free = sprite_id(sprite_id::value_base_t(i));
					}
				}
				std::fill_n(sprite.m_sprite_id.vptr() + new_size, old_size - new_size, uint16_t{});
				entity_resize(0);
			} else if(new_size > old_size) {
				sprite.first_free = sprite_id();
				int32_t i = int32_t(3000 - 1);
				for(; i >= int32_t(old_size); --i) {
					sprite.m__index.vptr()[i] = sprite.first_free;
					sprite.first_free = sprite_id(sprite_id::value_base_t(i));
				}
				for(; i >= 0; --i) {
					if(sprite.m__index.vptr()[i] != sprite_id(sprite_id::value_base_t(i))) {
						sprite.m__index.vptr()[i] = sprite.first_free;
						sprite.first_free = sprite_id(sprite_id::value_base_t(i));
					}
				}
			}
			sprite.size_used = new_size;
		}
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_entity(T&& func) {
			for(uint32_t i = 0; i < entity.size_used; ++i) {
				entity_id tmp = entity_id(entity_id::value_base_t(i));
				if(entity.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_entity;
		friend internal::object_iterator_entity;
		struct {
			internal::object_iterator_entity begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_entity));
				return internal::object_iterator_entity(*container, uint32_t(0));
			}
			internal::object_iterator_entity end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_entity));
				return internal::object_iterator_entity(*container, container->entity_size());
			}
			internal::const_object_iterator_entity begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_entity));
				return internal::const_object_iterator_entity(*container, uint32_t(0));
			}
			internal::const_object_iterator_entity end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_entity));
				return internal::const_object_iterator_entity(*container, container->entity_size());
			}
		}  in_entity ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_position(T&& func) {
			for(uint32_t i = 0; i < position.size_used; ++i) {
				position_id tmp = position_id(position_id::value_base_t(i));
				if(position.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_position;
		friend internal::object_iterator_position;
		struct {
			internal::object_iterator_position begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_position));
				return internal::object_iterator_position(*container, uint32_t(0));
			}
			internal::object_iterator_position end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_position));
				return internal::object_iterator_position(*container, container->position_size());
			}
			internal::const_object_iterator_position begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_position));
				return internal::const_object_iterator_position(*container, uint32_t(0));
			}
			internal::const_object_iterator_position end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_position));
				return internal::const_object_iterator_position(*container, container->position_size());
			}
		}  in_position ;
		
		template <typename T>
		DCON_RELEASE_INLINE void for_each_sprite(T&& func) {
			for(uint32_t i = 0; i < sprite.size_used; ++i) {
				sprite_id tmp = sprite_id(sprite_id::value_base_t(i));
				if(sprite.m__index.vptr()[tmp.index()] == tmp) func(tmp);
			}
		}
		friend internal::const_object_iterator_sprite;
		friend internal::object_iterator_sprite;
		struct {
			internal::object_iterator_sprite begin() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_sprite));
				return internal::object_iterator_sprite(*container, uint32_t(0));
			}
			internal::object_iterator_sprite end() {
				data_container* container = reinterpret_cast<data_container*>(reinterpret_cast<std::byte*>(this) - offsetof(data_container, in_sprite));
				return internal::object_iterator_sprite(*container, container->sprite_size());
			}
			internal::const_object_iterator_sprite begin() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_sprite));
				return internal::const_object_iterator_sprite(*container, uint32_t(0));
			}
			internal::const_object_iterator_sprite end() const {
				data_container const* container = reinterpret_cast<data_container const*>(reinterpret_cast<std::byte const*>(this) - offsetof(data_container, in_sprite));
				return internal::const_object_iterator_sprite(*container, container->sprite_size());
			}
		}  in_sprite ;
		

		friend internal::query_sprites_with_position_const_iterator;
		friend internal::query_sprites_with_position_iterator;
		internal::query_sprites_with_position_instance query_sprites_with_position() { return internal::query_sprites_with_position_instance(*this); }
		internal::query_sprites_with_position_const_instance query_sprites_with_position() const { return internal::query_sprites_with_position_const_instance(*this); }


		void reset() {
			entity_resize(0);
			position_resize(0);
			sprite_resize(0);
		}

		#ifndef DCON_NO_VE
		ve::vectorizable_buffer<float, entity_id> entity_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, entity_id>(entity.size_used);
		}
		ve::vectorizable_buffer<int32_t, entity_id> entity_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, entity_id>(entity.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_entity(F&& functor) {
			ve::execute_serial<entity_id>(entity.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_entity(F&& functor) {
			ve::execute_parallel_exact<entity_id>(entity.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, position_id> position_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, position_id>(position.size_used);
		}
		ve::vectorizable_buffer<int32_t, position_id> position_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, position_id>(position.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_position(F&& functor) {
			ve::execute_serial<position_id>(position.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_position(F&& functor) {
			ve::execute_parallel_exact<position_id>(position.size_used, functor);
		}
#endif
		ve::vectorizable_buffer<float, sprite_id> sprite_make_vectorizable_float_buffer() const noexcept {
			return ve::vectorizable_buffer<float, sprite_id>(sprite.size_used);
		}
		ve::vectorizable_buffer<int32_t, sprite_id> sprite_make_vectorizable_int_buffer() const noexcept {
			return ve::vectorizable_buffer<int32_t, sprite_id>(sprite.size_used);
		}
		template<typename F>
		DCON_RELEASE_INLINE void execute_serial_over_sprite(F&& functor) {
			ve::execute_serial<sprite_id>(sprite.size_used, functor);
		}
#ifndef VE_NO_TBB
		template<typename F>
		DCON_RELEASE_INLINE void execute_parallel_over_sprite(F&& functor) {
			ve::execute_parallel_exact<sprite_id>(sprite.size_used, functor);
		}
#endif
		#endif

		load_record serialize_entire_container_record() const noexcept {
			load_record result;
			result.entity = true;
			result.entity_position_component = true;
			result.entity_sprite_component = true;
			result.entity__index = true;
			result.position = true;
			result.position__index = true;
			result.position_x = true;
			result.position_y = true;
			result.position_rotation = true;
			result.sprite = true;
			result.sprite__index = true;
			result.sprite_sprite_id = true;
			return result;
		}
		
		//
		// calculate size (in bytes) required to serialize the desired objects, relationships, and properties
		//
		uint64_t serialize_size(load_record const& serialize_selection) const {
			uint64_t total_size = 0;
			if(serialize_selection.entity) {
				dcon::record_header header(0, "uint32_t", "entity", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
				if(serialize_selection.entity_position_component) {
					dcon::record_header iheader(0, "uint16_t", "entity", "position_component");
					total_size += iheader.serialize_size();
					total_size += sizeof(position_id) * entity.size_used;
				}
				if(serialize_selection.entity_sprite_component) {
					dcon::record_header iheader(0, "uint16_t", "entity", "sprite_component");
					total_size += iheader.serialize_size();
					total_size += sizeof(sprite_id) * entity.size_used;
				}
				dcon::record_header headerb(0, "$", "entity", "$index_end");
				total_size += headerb.serialize_size();
			}
			if(serialize_selection.entity__index) {
				dcon::record_header iheader(0, "uint16_t", "entity", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(entity_id) * entity.size_used;
			}
			if(serialize_selection.position) {
				dcon::record_header header(0, "uint32_t", "position", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.position__index) {
				dcon::record_header iheader(0, "uint16_t", "position", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(position_id) * position.size_used;
			}
			if(serialize_selection.position_x) {
				dcon::record_header iheader(0, "float", "position", "x");
				total_size += iheader.serialize_size();
				total_size += sizeof(float) * position.size_used;
			}
			if(serialize_selection.position_y) {
				dcon::record_header iheader(0, "float", "position", "y");
				total_size += iheader.serialize_size();
				total_size += sizeof(float) * position.size_used;
			}
			if(serialize_selection.position_rotation) {
				dcon::record_header iheader(0, "float", "position", "rotation");
				total_size += iheader.serialize_size();
				total_size += sizeof(float) * position.size_used;
			}
			if(serialize_selection.sprite) {
				dcon::record_header header(0, "uint32_t", "sprite", "$size");
				total_size += header.serialize_size();
				total_size += sizeof(uint32_t);
			}
			if(serialize_selection.sprite__index) {
				dcon::record_header iheader(0, "uint16_t", "sprite", "_index");
				total_size += iheader.serialize_size();
				total_size += sizeof(sprite_id) * sprite.size_used;
			}
			if(serialize_selection.sprite_sprite_id) {
				dcon::record_header iheader(0, "uint16_t", "sprite", "sprite_id");
				total_size += iheader.serialize_size();
				total_size += sizeof(uint16_t) * sprite.size_used;
			}
			return total_size;
		}
		
		//
		// serialize the desired objects, relationships, and properties
		//
		void serialize(std::byte*& output_buffer, load_record const& serialize_selection) const {
			if(serialize_selection.position) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "position", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = position.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.position__index) {
				dcon::record_header header(sizeof(position_id) * position.size_used, "uint16_t", "position", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<position_id*>(output_buffer), position.m__index.vptr(), sizeof(position_id) * position.size_used);
				output_buffer += sizeof(position_id) * position.size_used;
			}
			if(serialize_selection.position_x) {
				dcon::record_header header(sizeof(float) * position.size_used, "float", "position", "x");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<float*>(output_buffer), position.m_x.vptr(), sizeof(float) * position.size_used);
				output_buffer += sizeof(float) * position.size_used;
			}
			if(serialize_selection.position_y) {
				dcon::record_header header(sizeof(float) * position.size_used, "float", "position", "y");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<float*>(output_buffer), position.m_y.vptr(), sizeof(float) * position.size_used);
				output_buffer += sizeof(float) * position.size_used;
			}
			if(serialize_selection.position_rotation) {
				dcon::record_header header(sizeof(float) * position.size_used, "float", "position", "rotation");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<float*>(output_buffer), position.m_rotation.vptr(), sizeof(float) * position.size_used);
				output_buffer += sizeof(float) * position.size_used;
			}
			if(serialize_selection.sprite) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "sprite", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = sprite.size_used;
				output_buffer += sizeof(uint32_t);
			}
			if(serialize_selection.sprite__index) {
				dcon::record_header header(sizeof(sprite_id) * sprite.size_used, "uint16_t", "sprite", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<sprite_id*>(output_buffer), sprite.m__index.vptr(), sizeof(sprite_id) * sprite.size_used);
				output_buffer += sizeof(sprite_id) * sprite.size_used;
			}
			if(serialize_selection.sprite_sprite_id) {
				dcon::record_header header(sizeof(uint16_t) * sprite.size_used, "uint16_t", "sprite", "sprite_id");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<uint16_t*>(output_buffer), sprite.m_sprite_id.vptr(), sizeof(uint16_t) * sprite.size_used);
				output_buffer += sizeof(uint16_t) * sprite.size_used;
			}
			if(serialize_selection.entity) {
				dcon::record_header header(sizeof(uint32_t), "uint32_t", "entity", "$size");
				header.serialize(output_buffer);
				*(reinterpret_cast<uint32_t*>(output_buffer)) = entity.size_used;
				output_buffer += sizeof(uint32_t);
				 {
					dcon::record_header iheader(sizeof(position_id) * entity.size_used, "uint16_t", "entity", "position_component");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<position_id*>(output_buffer), entity.m_position_component.vptr(), sizeof(position_id) * entity.size_used);
					output_buffer += sizeof(position_id) *  entity.size_used;
				}
				 {
					dcon::record_header iheader(sizeof(sprite_id) * entity.size_used, "uint16_t", "entity", "sprite_component");
					iheader.serialize(output_buffer);
					std::memcpy(reinterpret_cast<sprite_id*>(output_buffer), entity.m_sprite_component.vptr(), sizeof(sprite_id) * entity.size_used);
					output_buffer += sizeof(sprite_id) *  entity.size_used;
				}
				dcon::record_header headerb(0, "$", "entity", "$index_end");
				headerb.serialize(output_buffer);
			}
			if(serialize_selection.entity__index) {
				dcon::record_header header(sizeof(entity_id) * entity.size_used, "uint16_t", "entity", "_index");
				header.serialize(output_buffer);
				std::memcpy(reinterpret_cast<entity_id*>(output_buffer), entity.m__index.vptr(), sizeof(entity_id) * entity.size_used);
				output_buffer += sizeof(entity_id) * entity.size_used;
			}
		}
		
		//
		// deserialize the desired objects, relationships, and properties
		//
		void deserialize(std::byte const*& input_buffer, std::byte const* end, load_record& serialize_selection) {
			while(input_buffer < end) {
				dcon::record_header header;
				header.deserialize(input_buffer, end);
				if(input_buffer + header.record_size <= end) {
					do {
						if(header.is_object("entity")) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= entity.size_used) {
										entity_resize(0);
									}
									entity_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.entity = true;
									break;
								}
								if(header.is_property("_index")) {
									if(header.is_type("uint16_t")) {
										std::memcpy(entity.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(entity.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.entity__index = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											entity.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.entity__index = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											entity.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.entity__index = true;
									}
									if(serialize_selection.entity__index == true) {
										entity.first_free = entity_id();
										for(int32_t j = 3000 - 1; j >= 0; --j) {
											if(entity.m__index.vptr()[j] != entity_id(uint16_t(j))) {
												entity.m__index.vptr()[j] = entity.first_free;
												entity.first_free = entity_id(uint16_t(j));
											} else {
											}
										}
									}
									break;
								}
								if(header.is_property("position_component")) {
									if(header.is_type("uint16_t")) {
										std::memcpy(entity.m_position_component.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(entity.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.entity_position_component = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											entity.m_position_component.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.entity_position_component = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											entity.m_position_component.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.entity_position_component = true;
									}
									break;
								}
								if(header.is_property("sprite_component")) {
									if(header.is_type("uint16_t")) {
										std::memcpy(entity.m_sprite_component.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(entity.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.entity_sprite_component = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											entity.m_sprite_component.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.entity_sprite_component = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											entity.m_sprite_component.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.entity_sprite_component = true;
									}
									break;
								}
								if(header.is_property("$index_end")) {
									if(serialize_selection.entity_position_component == true) {
										for(uint32_t i = 0; i < entity.size_used; ++i) {
											auto tmp = entity.m_position_component.vptr()[i];
											entity.m_position_component.vptr()[i] = position_id();
											internal_entity_set_position_component(entity_id(entity_id::value_base_t(i)), tmp);
										}
									}
									if(serialize_selection.entity_sprite_component == true) {
										for(uint32_t i = 0; i < entity.size_used; ++i) {
											auto tmp = entity.m_sprite_component.vptr()[i];
											entity.m_sprite_component.vptr()[i] = sprite_id();
											internal_entity_set_sprite_component(entity_id(entity_id::value_base_t(i)), tmp);
										}
									}
									break;
								}
							} while(false);
							break;
						}
						if(header.is_object("position")) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									position_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.position = true;
									break;
								}
								if(header.is_property("_index")) {
									if(header.is_type("uint16_t")) {
										std::memcpy(position.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(position.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.position__index = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											position.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.position__index = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											position.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.position__index = true;
									}
									if(serialize_selection.position__index == true) {
										position.first_free = position_id();
										for(int32_t j = 3000 - 1; j >= 0; --j) {
											if(position.m__index.vptr()[j] != position_id(uint16_t(j))) {
												position.m__index.vptr()[j] = position.first_free;
												position.first_free = position_id(uint16_t(j));
											} else {
											}
										}
									}
									break;
								}
								if(header.is_property("x")) {
									if(header.is_type("float")) {
										std::memcpy(position.m_x.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(position.size_used) * sizeof(float), header.record_size));
										serialize_selection.position_x = true;
									}
									else if(header.is_type("int8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("int16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("int32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("int64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("uint64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("double")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									break;
								}
								if(header.is_property("y")) {
									if(header.is_type("float")) {
										std::memcpy(position.m_y.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(position.size_used) * sizeof(float), header.record_size));
										serialize_selection.position_y = true;
									}
									else if(header.is_type("int8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("int16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("int32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("int64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("uint64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("double")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									break;
								}
								if(header.is_property("rotation")) {
									if(header.is_type("float")) {
										std::memcpy(position.m_rotation.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(position.size_used) * sizeof(float), header.record_size));
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("int8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("int16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("int32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("int64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("uint64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("double")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									break;
								}
							} while(false);
							break;
						}
						if(header.is_object("sprite")) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									sprite_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.sprite = true;
									break;
								}
								if(header.is_property("_index")) {
									if(header.is_type("uint16_t")) {
										std::memcpy(sprite.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(sprite.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.sprite__index = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											sprite.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite__index = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											sprite.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite__index = true;
									}
									if(serialize_selection.sprite__index == true) {
										sprite.first_free = sprite_id();
										for(int32_t j = 3000 - 1; j >= 0; --j) {
											if(sprite.m__index.vptr()[j] != sprite_id(uint16_t(j))) {
												sprite.m__index.vptr()[j] = sprite.first_free;
												sprite.first_free = sprite_id(uint16_t(j));
											} else {
											}
										}
									}
									break;
								}
								if(header.is_property("sprite_id")) {
									if(header.is_type("uint16_t")) {
										std::memcpy(sprite.m_sprite_id.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(sprite.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("int8_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("int16_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("int32_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("int64_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("uint64_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("float")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<float const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("double")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<double const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									break;
								}
							} while(false);
							break;
						}
					} while(false);
				}
				input_buffer += header.record_size;
			}
		}
		
		//
		// deserialize the desired objects, relationships, and properties where the mask is set
		//
		void deserialize(std::byte const*& input_buffer, std::byte const* end, load_record& serialize_selection, load_record const& mask) {
			while(input_buffer < end) {
				dcon::record_header header;
				header.deserialize(input_buffer, end);
				if(input_buffer + header.record_size <= end) {
					do {
						if(header.is_object("entity") && mask.entity) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									if(*(reinterpret_cast<uint32_t const*>(input_buffer)) >= entity.size_used) {
										entity_resize(0);
									}
									entity_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.entity = true;
									break;
								}
								if(header.is_property("_index") && mask.entity__index) {
									if(header.is_type("uint16_t")) {
										std::memcpy(entity.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(entity.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.entity__index = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											entity.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.entity__index = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											entity.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.entity__index = true;
									}
									if(serialize_selection.entity__index == true) {
										entity.first_free = entity_id();
										for(int32_t j = 3000 - 1; j >= 0; --j) {
											if(entity.m__index.vptr()[j] != entity_id(uint16_t(j))) {
												entity.m__index.vptr()[j] = entity.first_free;
												entity.first_free = entity_id(uint16_t(j));
											} else {
											}
										}
									}
									break;
								}
								if(header.is_property("position_component") && mask.entity_position_component) {
									if(header.is_type("uint16_t")) {
										std::memcpy(entity.m_position_component.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(entity.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.entity_position_component = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											entity.m_position_component.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.entity_position_component = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											entity.m_position_component.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.entity_position_component = true;
									}
									break;
								}
								if(header.is_property("sprite_component") && mask.entity_sprite_component) {
									if(header.is_type("uint16_t")) {
										std::memcpy(entity.m_sprite_component.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(entity.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.entity_sprite_component = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											entity.m_sprite_component.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.entity_sprite_component = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(entity.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											entity.m_sprite_component.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.entity_sprite_component = true;
									}
									break;
								}
								if(header.is_property("$index_end") && mask.entity) {
									if(serialize_selection.entity_position_component == true) {
										for(uint32_t i = 0; i < entity.size_used; ++i) {
											auto tmp = entity.m_position_component.vptr()[i];
											entity.m_position_component.vptr()[i] = position_id();
											internal_entity_set_position_component(entity_id(entity_id::value_base_t(i)), tmp);
										}
									}
									if(serialize_selection.entity_sprite_component == true) {
										for(uint32_t i = 0; i < entity.size_used; ++i) {
											auto tmp = entity.m_sprite_component.vptr()[i];
											entity.m_sprite_component.vptr()[i] = sprite_id();
											internal_entity_set_sprite_component(entity_id(entity_id::value_base_t(i)), tmp);
										}
									}
									break;
								}
							} while(false);
							break;
						}
						if(header.is_object("position") && mask.position) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									position_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.position = true;
									break;
								}
								if(header.is_property("_index") && mask.position__index) {
									if(header.is_type("uint16_t")) {
										std::memcpy(position.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(position.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.position__index = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											position.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.position__index = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											position.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.position__index = true;
									}
									if(serialize_selection.position__index == true) {
										position.first_free = position_id();
										for(int32_t j = 3000 - 1; j >= 0; --j) {
											if(position.m__index.vptr()[j] != position_id(uint16_t(j))) {
												position.m__index.vptr()[j] = position.first_free;
												position.first_free = position_id(uint16_t(j));
											} else {
											}
										}
									}
									break;
								}
								if(header.is_property("x") && mask.position_x) {
									if(header.is_type("float")) {
										std::memcpy(position.m_x.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(position.size_used) * sizeof(float), header.record_size));
										serialize_selection.position_x = true;
									}
									else if(header.is_type("int8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("int16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("int32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("int64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("uint64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									else if(header.is_type("double")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
											position.m_x.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
										}
										serialize_selection.position_x = true;
									}
									break;
								}
								if(header.is_property("y") && mask.position_y) {
									if(header.is_type("float")) {
										std::memcpy(position.m_y.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(position.size_used) * sizeof(float), header.record_size));
										serialize_selection.position_y = true;
									}
									else if(header.is_type("int8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("int16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("int32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("int64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("uint64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									else if(header.is_type("double")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
											position.m_y.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
										}
										serialize_selection.position_y = true;
									}
									break;
								}
								if(header.is_property("rotation") && mask.position_rotation) {
									if(header.is_type("float")) {
										std::memcpy(position.m_rotation.vptr(), reinterpret_cast<float const*>(input_buffer), std::min(size_t(position.size_used) * sizeof(float), header.record_size));
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("int8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("int16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("uint16_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint16_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<uint16_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("int32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("int64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("uint64_t")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									else if(header.is_type("double")) {
										for(uint32_t i = 0; i < std::min(position.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
											position.m_rotation.vptr()[i] = float(*(reinterpret_cast<double const*>(input_buffer) + i));
										}
										serialize_selection.position_rotation = true;
									}
									break;
								}
							} while(false);
							break;
						}
						if(header.is_object("sprite") && mask.sprite) {
							do {
								if(header.is_property("$size") && header.record_size == sizeof(uint32_t)) {
									sprite_resize(*(reinterpret_cast<uint32_t const*>(input_buffer)));
									serialize_selection.sprite = true;
									break;
								}
								if(header.is_property("_index") && mask.sprite__index) {
									if(header.is_type("uint16_t")) {
										std::memcpy(sprite.m__index.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(sprite.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.sprite__index = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											sprite.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite__index = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											sprite.m__index.vptr()[i].value = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite__index = true;
									}
									if(serialize_selection.sprite__index == true) {
										sprite.first_free = sprite_id();
										for(int32_t j = 3000 - 1; j >= 0; --j) {
											if(sprite.m__index.vptr()[j] != sprite_id(uint16_t(j))) {
												sprite.m__index.vptr()[j] = sprite.first_free;
												sprite.first_free = sprite_id(uint16_t(j));
											} else {
											}
										}
									}
									break;
								}
								if(header.is_property("sprite_id") && mask.sprite_sprite_id) {
									if(header.is_type("uint16_t")) {
										std::memcpy(sprite.m_sprite_id.vptr(), reinterpret_cast<uint16_t const*>(input_buffer), std::min(size_t(sprite.size_used) * sizeof(uint16_t), header.record_size));
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("int8_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(int8_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<int8_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("uint8_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(uint8_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<uint8_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("int16_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(int16_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<int16_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("int32_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(int32_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<int32_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("uint32_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(uint32_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<uint32_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("int64_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(int64_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<int64_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("uint64_t")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(uint64_t))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<uint64_t const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("float")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(float))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<float const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									else if(header.is_type("double")) {
										for(uint32_t i = 0; i < std::min(sprite.size_used, uint32_t(header.record_size / sizeof(double))); ++i) {
											sprite.m_sprite_id.vptr()[i] = uint16_t(*(reinterpret_cast<double const*>(input_buffer) + i));
										}
										serialize_selection.sprite_sprite_id = true;
									}
									break;
								}
							} while(false);
							break;
						}
					} while(false);
				}
				input_buffer += header.record_size;
			}
		}
		

	};

	DCON_RELEASE_INLINE position_fat_id entity_fat_id::get_position_component() const noexcept {
		return position_fat_id(container, container.entity_get_position_component(id));
	}
	DCON_RELEASE_INLINE void entity_fat_id::set_position_component(position_id val) const noexcept {
		container.entity_set_position_component(id, val);
	}
	DCON_RELEASE_INLINE bool entity_fat_id::try_set_position_component(position_id val) const noexcept {
		return container.entity_try_set_position_component(id, val);
	}
	DCON_RELEASE_INLINE sprite_fat_id entity_fat_id::get_sprite_component() const noexcept {
		return sprite_fat_id(container, container.entity_get_sprite_component(id));
	}
	DCON_RELEASE_INLINE void entity_fat_id::set_sprite_component(sprite_id val) const noexcept {
		container.entity_set_sprite_component(id, val);
	}
	DCON_RELEASE_INLINE bool entity_fat_id::try_set_sprite_component(sprite_id val) const noexcept {
		return container.entity_try_set_sprite_component(id, val);
	}
	DCON_RELEASE_INLINE bool entity_fat_id::is_valid() const noexcept {
		return container.entity_is_valid(id);
	}
	
	DCON_RELEASE_INLINE position_const_fat_id entity_const_fat_id::get_position_component() const noexcept {
		return position_const_fat_id(container, container.entity_get_position_component(id));
	}
	DCON_RELEASE_INLINE sprite_const_fat_id entity_const_fat_id::get_sprite_component() const noexcept {
		return sprite_const_fat_id(container, container.entity_get_sprite_component(id));
	}
	DCON_RELEASE_INLINE bool entity_const_fat_id::is_valid() const noexcept {
		return container.entity_is_valid(id);
	}
	
	DCON_RELEASE_INLINE float& position_fat_id::get_x() const noexcept {
		return container.position_get_x(id);
	}
	DCON_RELEASE_INLINE void position_fat_id::set_x(float v) const noexcept {
		container.position_set_x(id, v);
	}
	DCON_RELEASE_INLINE float& position_fat_id::get_y() const noexcept {
		return container.position_get_y(id);
	}
	DCON_RELEASE_INLINE void position_fat_id::set_y(float v) const noexcept {
		container.position_set_y(id, v);
	}
	DCON_RELEASE_INLINE float& position_fat_id::get_rotation() const noexcept {
		return container.position_get_rotation(id);
	}
	DCON_RELEASE_INLINE void position_fat_id::set_rotation(float v) const noexcept {
		container.position_set_rotation(id, v);
	}
	DCON_RELEASE_INLINE entity_fat_id position_fat_id::get_entity_as_position_component() const noexcept {
		return entity_fat_id(container, container.position_get_entity_as_position_component(id));
	}
	DCON_RELEASE_INLINE void position_fat_id::remove_entity_as_position_component() const noexcept {
		container.position_remove_entity_as_position_component(id);
	}
	DCON_RELEASE_INLINE entity_fat_id position_fat_id::get_entity() const noexcept {
		return entity_fat_id(container, container.position_get_entity(id));
	}
	DCON_RELEASE_INLINE void position_fat_id::remove_entity() const noexcept {
		container.position_remove_entity(id);
	}
	DCON_RELEASE_INLINE sprite_fat_id position_fat_id::get_sprite_component_from_entity() const noexcept {
		return sprite_fat_id(container, container.position_get_sprite_component_from_entity(id));
	}
	DCON_RELEASE_INLINE void position_fat_id::set_sprite_component_from_entity(sprite_id v) const noexcept {
		container.position_set_sprite_component_from_entity(id, v);
	}
	DCON_RELEASE_INLINE bool position_fat_id::is_valid() const noexcept {
		return container.position_is_valid(id);
	}
	
	DCON_RELEASE_INLINE float position_const_fat_id::get_x() const noexcept {
		return container.position_get_x(id);
	}
	DCON_RELEASE_INLINE float position_const_fat_id::get_y() const noexcept {
		return container.position_get_y(id);
	}
	DCON_RELEASE_INLINE float position_const_fat_id::get_rotation() const noexcept {
		return container.position_get_rotation(id);
	}
	DCON_RELEASE_INLINE entity_const_fat_id position_const_fat_id::get_entity_as_position_component() const noexcept {
		return entity_const_fat_id(container, container.position_get_entity_as_position_component(id));
	}
	DCON_RELEASE_INLINE entity_const_fat_id position_const_fat_id::get_entity() const noexcept {
		return entity_const_fat_id(container, container.position_get_entity(id));
	}
	DCON_RELEASE_INLINE sprite_const_fat_id position_const_fat_id::get_sprite_component_from_entity() const noexcept {
		return sprite_const_fat_id(container, container.position_get_sprite_component_from_entity(id));
	}
	DCON_RELEASE_INLINE bool position_const_fat_id::is_valid() const noexcept {
		return container.position_is_valid(id);
	}
	
	DCON_RELEASE_INLINE uint16_t& sprite_fat_id::get_sprite_id() const noexcept {
		return container.sprite_get_sprite_id(id);
	}
	DCON_RELEASE_INLINE void sprite_fat_id::set_sprite_id(uint16_t v) const noexcept {
		container.sprite_set_sprite_id(id, v);
	}
	DCON_RELEASE_INLINE entity_fat_id sprite_fat_id::get_entity_as_sprite_component() const noexcept {
		return entity_fat_id(container, container.sprite_get_entity_as_sprite_component(id));
	}
	DCON_RELEASE_INLINE void sprite_fat_id::remove_entity_as_sprite_component() const noexcept {
		container.sprite_remove_entity_as_sprite_component(id);
	}
	DCON_RELEASE_INLINE entity_fat_id sprite_fat_id::get_entity() const noexcept {
		return entity_fat_id(container, container.sprite_get_entity(id));
	}
	DCON_RELEASE_INLINE void sprite_fat_id::remove_entity() const noexcept {
		container.sprite_remove_entity(id);
	}
	DCON_RELEASE_INLINE position_fat_id sprite_fat_id::get_position_component_from_entity() const noexcept {
		return position_fat_id(container, container.sprite_get_position_component_from_entity(id));
	}
	DCON_RELEASE_INLINE void sprite_fat_id::set_position_component_from_entity(position_id v) const noexcept {
		container.sprite_set_position_component_from_entity(id, v);
	}
	DCON_RELEASE_INLINE bool sprite_fat_id::is_valid() const noexcept {
		return container.sprite_is_valid(id);
	}
	
	DCON_RELEASE_INLINE uint16_t sprite_const_fat_id::get_sprite_id() const noexcept {
		return container.sprite_get_sprite_id(id);
	}
	DCON_RELEASE_INLINE entity_const_fat_id sprite_const_fat_id::get_entity_as_sprite_component() const noexcept {
		return entity_const_fat_id(container, container.sprite_get_entity_as_sprite_component(id));
	}
	DCON_RELEASE_INLINE entity_const_fat_id sprite_const_fat_id::get_entity() const noexcept {
		return entity_const_fat_id(container, container.sprite_get_entity(id));
	}
	DCON_RELEASE_INLINE position_const_fat_id sprite_const_fat_id::get_position_component_from_entity() const noexcept {
		return position_const_fat_id(container, container.sprite_get_position_component_from_entity(id));
	}
	DCON_RELEASE_INLINE bool sprite_const_fat_id::is_valid() const noexcept {
		return container.sprite_is_valid(id);
	}
	

	namespace internal {
		class query_sprites_with_position_instance;
		class query_sprites_with_position_const_instance;
		class query_sprites_with_position_iterator {
			private:
			data_container& m_container;
			query_sprites_with_position_instance& m_parameters;
			sprite_id m_tableindex0;
			entity_id m_tableindex1;
			position_id m_tableindex2;
			public:
			query_sprites_with_position_iterator(data_container& c, query_sprites_with_position_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.sprite_size() > 0) {
					internal_init(sprite_id(sprite_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_sprites_with_position_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_sprites_with_position_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(sprite_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(sprite_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(entity_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(position_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			sprite_fat_id get_sprite() const noexcept;
			position_fat_id get_position() const noexcept;
			bool has_sprite() const noexcept;
			bool has_entity() const noexcept;
			bool has_position() const noexcept;
			
		};
		class query_sprites_with_position_const_iterator {
			private:
			data_container const& m_container;
			query_sprites_with_position_const_instance& m_parameters;
			sprite_id m_tableindex0;
			entity_id m_tableindex1;
			position_id m_tableindex2;
			public:
			query_sprites_with_position_const_iterator(data_container const& c, query_sprites_with_position_const_instance& p) : m_container(c), m_parameters(p) {
				if(m_container.sprite_size() > 0) {
					internal_init(sprite_id(sprite_id::value_base_t(0)));
				}
			}
			auto operator++() -> query_sprites_with_position_const_iterator&;
			bool operator==(dcon::invalid_iterator_type);
			bool operator!=(dcon::invalid_iterator_type);
			auto operator*() -> query_sprites_with_position_const_iterator const&;
			private:
			void internal_reset_aggregates();
			void internal_set_aggregates();
			void internal_update_aggregates();
			void internal_init(sprite_id first_value);
			void internal_increment_to_result(bool);
			void internal_reset_v0();
			bool internal_set_v0(sprite_id v);
			bool internal_increment_v0(bool, bool&);
			void internal_reset_v1();
			bool internal_set_v1(entity_id v);
			bool internal_increment_v1(bool force, bool& hit_group);
			void internal_reset_v2();
			bool internal_set_v2(position_id v);
			bool internal_increment_v2(bool force, bool& hit_group);
			public:
			sprite_const_fat_id get_sprite() const noexcept;
			position_const_fat_id get_position() const noexcept;
			bool has_sprite() const noexcept;
			bool has_entity() const noexcept;
			bool has_position() const noexcept;
			
		};
		
		query_sprites_with_position_iterator query_sprites_with_position_instance::begin() {
			return query_sprites_with_position_iterator(container, *this);
		}
		query_sprites_with_position_const_iterator query_sprites_with_position_const_instance::begin() {
			return query_sprites_with_position_const_iterator(container, *this);
		}
		DCON_RELEASE_INLINE object_iterator_entity::object_iterator_entity(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.entity.m__index.vptr()[index] != entity_id(entity_id::value_base_t(index)) && index < container.entity.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_entity::const_object_iterator_entity(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.entity.m__index.vptr()[index] != entity_id(entity_id::value_base_t(index)) && index < container.entity.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_entity& object_iterator_entity::operator++() noexcept {
			++index;
			while(container.entity.m__index.vptr()[index] != entity_id(entity_id::value_base_t(index)) && index < container.entity.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_entity& const_object_iterator_entity::operator++() noexcept {
			++index;
			while(container.entity.m__index.vptr()[index] != entity_id(entity_id::value_base_t(index)) && index < container.entity.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_entity& object_iterator_entity::operator--() noexcept {
			--index;
			while(container.entity.m__index.vptr()[index] != entity_id(entity_id::value_base_t(index)) && index < container.entity.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_entity& const_object_iterator_entity::operator--() noexcept {
			--index;
			while(container.entity.m__index.vptr()[index] != entity_id(entity_id::value_base_t(index)) && index < container.entity.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_position::object_iterator_position(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.position.m__index.vptr()[index] != position_id(position_id::value_base_t(index)) && index < container.position.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_position::const_object_iterator_position(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.position.m__index.vptr()[index] != position_id(position_id::value_base_t(index)) && index < container.position.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_position& object_iterator_position::operator++() noexcept {
			++index;
			while(container.position.m__index.vptr()[index] != position_id(position_id::value_base_t(index)) && index < container.position.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_position& const_object_iterator_position::operator++() noexcept {
			++index;
			while(container.position.m__index.vptr()[index] != position_id(position_id::value_base_t(index)) && index < container.position.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_position& object_iterator_position::operator--() noexcept {
			--index;
			while(container.position.m__index.vptr()[index] != position_id(position_id::value_base_t(index)) && index < container.position.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_position& const_object_iterator_position::operator--() noexcept {
			--index;
			while(container.position.m__index.vptr()[index] != position_id(position_id::value_base_t(index)) && index < container.position.size_used) {
				--index;
			}
			return *this;
		}
		
		DCON_RELEASE_INLINE object_iterator_sprite::object_iterator_sprite(data_container& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.sprite.m__index.vptr()[index] != sprite_id(sprite_id::value_base_t(index)) && index < container.sprite.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE const_object_iterator_sprite::const_object_iterator_sprite(data_container const& c, uint32_t i) noexcept : container(c), index(i) {
			while(container.sprite.m__index.vptr()[index] != sprite_id(sprite_id::value_base_t(index)) && index < container.sprite.size_used) {
				++index;
			}
		}
		DCON_RELEASE_INLINE object_iterator_sprite& object_iterator_sprite::operator++() noexcept {
			++index;
			while(container.sprite.m__index.vptr()[index] != sprite_id(sprite_id::value_base_t(index)) && index < container.sprite.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_sprite& const_object_iterator_sprite::operator++() noexcept {
			++index;
			while(container.sprite.m__index.vptr()[index] != sprite_id(sprite_id::value_base_t(index)) && index < container.sprite.size_used) {
				++index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE object_iterator_sprite& object_iterator_sprite::operator--() noexcept {
			--index;
			while(container.sprite.m__index.vptr()[index] != sprite_id(sprite_id::value_base_t(index)) && index < container.sprite.size_used) {
				--index;
			}
			return *this;
		}
		DCON_RELEASE_INLINE const_object_iterator_sprite& const_object_iterator_sprite::operator--() noexcept {
			--index;
			while(container.sprite.m__index.vptr()[index] != sprite_id(sprite_id::value_base_t(index)) && index < container.sprite.size_used) {
				--index;
			}
			return *this;
		}
		
	};


	auto internal::query_sprites_with_position_const_iterator::operator++() -> query_sprites_with_position_const_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_sprites_with_position_const_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_sprites_with_position_const_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_sprites_with_position_const_iterator::operator*() -> query_sprites_with_position_const_iterator const& {
		return *this;
	}
	void internal::query_sprites_with_position_const_iterator::internal_reset_aggregates() {
	}
	void internal::query_sprites_with_position_const_iterator::internal_set_aggregates() {
	}
	void internal::query_sprites_with_position_const_iterator::internal_update_aggregates() {
	}
	void internal::query_sprites_with_position_const_iterator::internal_init(sprite_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_sprites_with_position_const_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_sprites_with_position_const_iterator::internal_reset_v0() {
		m_tableindex0 = sprite_id();
		internal_reset_v1();
	}
	bool internal::query_sprites_with_position_const_iterator::internal_set_v0(sprite_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		return internal_set_v1(m_container.sprite_get_entity_as_sprite_component(m_tableindex0));
		}() && 
		true;
	}
	bool internal::query_sprites_with_position_const_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.sprite_size(); ++i) {
			if(m_container.sprite_is_valid( sprite_id(sprite_id::value_base_t(i)) )) {
				if(internal_set_v0( sprite_id(sprite_id::value_base_t(i)) )) return true;
			}
		}
		m_tableindex0 = sprite_id( );
		return false;
	}
	void internal::query_sprites_with_position_const_iterator::internal_reset_v1() {
		m_tableindex1 = entity_id();
		internal_reset_v2();
	}
	bool internal::query_sprites_with_position_const_iterator::internal_set_v1(entity_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.entity_get_position_component(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_sprites_with_position_const_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		return internal_increment_v0(force, hit_group);
	}
	void internal::query_sprites_with_position_const_iterator::internal_reset_v2() {
		m_tableindex2 = position_id();
	}
	bool internal::query_sprites_with_position_const_iterator::internal_set_v2(position_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_sprites_with_position_const_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	sprite_const_fat_id internal::query_sprites_with_position_const_iterator::get_sprite() const noexcept {
		return sprite_const_fat_id(m_container, m_tableindex0 );
	}
	position_const_fat_id internal::query_sprites_with_position_const_iterator::get_position() const noexcept {
		return position_const_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_sprites_with_position_const_iterator::has_sprite() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_sprites_with_position_const_iterator::has_entity() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_sprites_with_position_const_iterator::has_position() const noexcept {
		return bool(m_tableindex2);
	}
	
	auto internal::query_sprites_with_position_iterator::operator++() -> query_sprites_with_position_iterator& {
		internal_increment_to_result(true);
		return *this;
	}
	bool internal::query_sprites_with_position_iterator::operator==(dcon::invalid_iterator_type) {
		return !bool(m_tableindex0);
	}
	bool internal::query_sprites_with_position_iterator::operator!=(dcon::invalid_iterator_type) {
		return bool(m_tableindex0);
	}
	auto internal::query_sprites_with_position_iterator::operator*() -> query_sprites_with_position_iterator const& {
		return *this;
	}
	void internal::query_sprites_with_position_iterator::internal_reset_aggregates() {
	}
	void internal::query_sprites_with_position_iterator::internal_set_aggregates() {
	}
	void internal::query_sprites_with_position_iterator::internal_update_aggregates() {
	}
	void internal::query_sprites_with_position_iterator::internal_init(sprite_id first_value) {
		if(internal_set_v0(first_value)) {
			return;
		}
		internal_increment_to_result(true);
	}
	void internal::query_sprites_with_position_iterator::internal_increment_to_result(bool) {
		bool hit_group = false;
		while(bool(m_tableindex0)) {
			while(bool(m_tableindex0) && !internal_increment_v2(false, hit_group)) {
			}
			return;
		}
	}
	void internal::query_sprites_with_position_iterator::internal_reset_v0() {
		m_tableindex0 = sprite_id();
		internal_reset_v1();
	}
	bool internal::query_sprites_with_position_iterator::internal_set_v0(sprite_id v) {
		if(!bool(v)) {
			m_tableindex0 = v;
			return false;
		}
		m_tableindex0 = v;
		return 
		[&](){
		return internal_set_v1(m_container.sprite_get_entity_as_sprite_component(m_tableindex0));
		}() && 
		true;
	}
	bool internal::query_sprites_with_position_iterator::internal_increment_v0(bool, bool&) {
		for(uint32_t i = uint32_t(m_tableindex0.index() + 1); i < m_container.sprite_size(); ++i) {
			if(m_container.sprite_is_valid( sprite_id(sprite_id::value_base_t(i)) )) {
				if(internal_set_v0( sprite_id(sprite_id::value_base_t(i)) )) return true;
			}
		}
		m_tableindex0 = sprite_id( );
		return false;
	}
	void internal::query_sprites_with_position_iterator::internal_reset_v1() {
		m_tableindex1 = entity_id();
		internal_reset_v2();
	}
	bool internal::query_sprites_with_position_iterator::internal_set_v1(entity_id v) {
		if(!bool(v)) {
			m_tableindex1 = v;
			return false;
		}
		m_tableindex1 = v;
		return 
		[&](){
		return internal_set_v2( m_container.entity_get_position_component(m_tableindex1) );
		}() && 
		true;
	}
	bool internal::query_sprites_with_position_iterator::internal_increment_v1(bool force, bool& hit_group) {
		if(!bool(m_tableindex1)) {
			return internal_increment_v0(force, hit_group);
		}
		return internal_increment_v0(force, hit_group);
	}
	void internal::query_sprites_with_position_iterator::internal_reset_v2() {
		m_tableindex2 = position_id();
	}
	bool internal::query_sprites_with_position_iterator::internal_set_v2(position_id v) {
		if(!bool(v)) {
			m_tableindex2 = v;
			return false;
		}
		m_tableindex2 = v;
		return 
		true;
	}
	bool internal::query_sprites_with_position_iterator::internal_increment_v2(bool force, bool& hit_group) {
		if(!bool(m_tableindex2)) {
			return internal_increment_v1(force, hit_group);
		}
		return internal_increment_v1(force, hit_group);
	}
	sprite_fat_id internal::query_sprites_with_position_iterator::get_sprite() const noexcept {
		return sprite_fat_id(m_container, m_tableindex0 );
	}
	position_fat_id internal::query_sprites_with_position_iterator::get_position() const noexcept {
		return position_fat_id(m_container, m_tableindex2 );
	}
	bool internal::query_sprites_with_position_iterator::has_sprite() const noexcept {
		return bool(m_tableindex0);
	}
	bool internal::query_sprites_with_position_iterator::has_entity() const noexcept {
		return bool(m_tableindex1);
	}
	bool internal::query_sprites_with_position_iterator::has_position() const noexcept {
		return bool(m_tableindex2);
	}
	
}

#undef DCON_RELEASE_INLINE
#ifdef _MSC_VER
#pragma warning( pop )
#endif

