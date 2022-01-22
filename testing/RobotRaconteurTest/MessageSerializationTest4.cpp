﻿#ifdef ROBOTRACONTEUR_USE_STDAFX
#include "stdafx.h"
#endif

#include "MessageSerializationTest4.h"

using namespace RobotRaconteur;


#include <RobotRaconteur.h>

#include <time.h>

#include <RobotRaconteur/StringTable.h>

#include "MessageSerializationTest.h"

#include <boost/random.hpp>

using namespace boost::random;

namespace RobotRaconteurTest
{
	static uint8_t MessageSerializationTest4_NewRandomMessageFlags(mt19937& rng)
	{
		uniform_int_distribution<uint16_t> bit_dist(0, 1);
		uint8_t o = 0;
		for (size_t i = 0; i < 8; i++)
		{
			o = (o << 1) | bit_dist(rng);
		}
		return o;
	}

	static uint8_t MessageSerializationTest4_NewRandomFlags(mt19937& rng)
	{
		uniform_int_distribution<uint8_t> bit_dist(0, 1);
		uint8_t o = 0;
		for (size_t i = 0; i < 8; i++)
		{
			o = (o << 1) | bit_dist(rng);
		}
		return o;
	}

	static std::string MessageSerializationTest4_NewRandomString(mt19937& rng, size_t max_len)
	{
		std::stringstream buf;
		std::string chars(
			"abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"1234567890");

		uniform_int_distribution<uint32_t> size_t_dist(0, max_len);
		size_t l = size_t_dist(rng);

		boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
		for (size_t i = 0; i < l; ++i) {
			buf << chars[index_dist(rng)];
		}

		return buf.str();

	}

	static std::vector<uint8_t> MessageSerializationTest4_NewRandomExtended(mt19937& rng, size_t max_len)
	{
		uniform_int_distribution<uint32_t> size_t_dist(0, max_len);
		size_t l = size_t_dist(rng);

		std::vector<uint8_t> buf(l);

		boost::random::uniform_int_distribution<uint8_t> value_dist;

		for (size_t i=0; i<l; i++)
		{
			buf[i] = value_dist(rng);
		}

		return buf;

	}

	static RR_INTRUSIVE_PTR<MessageElement> MessageSerializationTest4_NewRandomMessageElement(mt19937& rng, size_t depth)
	{
		uniform_int_distribution<uint16_t> type_switch_dist(0, 1);
		uniform_int_distribution<uint16_t> type_dist(0, 11);
		uniform_int_distribution<uint16_t> n_type_dist(0, 9);
		uniform_int_distribution<uint8_t>  uint8_dist;
		uniform_int_distribution<uint32_t> uint32_dist;
		uniform_int_distribution<int32_t> int32_dist;
		uniform_int_distribution<size_t> len_dist(0,256);
		uniform_int_distribution<size_t> len_sub_dist(1, 8);
		RR_INTRUSIVE_PTR<MessageElement> e = CreateMessageElement();
		e->ElementFlags = MessageSerializationTest4_NewRandomFlags(rng);
		e->ElementFlags &= ~0x40;		
		if (type_switch_dist(rng) == 0 || depth > 2)
		{
			e->ElementType = (DataTypes)type_dist(rng);
		}
		else
		{
			uint16_t t1 = n_type_dist(rng);
			switch (t1)
			{
			case 0:
				e->ElementType = DataTypes_structure_t;
				break;
			case 1:
				e->ElementType = DataTypes_vector_t;
				break;
			case 2:
				e->ElementType = DataTypes_dictionary_t;
				break;
			case 3:
				e->ElementType = DataTypes_multidimarray_t;
				break;
			case 4:
				e->ElementType = DataTypes_list_t;
				break;
			case 5:
				e->ElementType = DataTypes_pod_t;
				break;
			case 6:
				e->ElementType = DataTypes_pod_array_t;
				break;
			case 7:
				e->ElementType = DataTypes_pod_multidimarray_t;
				break;
			case 8:
				e->ElementType = DataTypes_namedarray_array_t;
				break;
			case 9:
				e->ElementType = DataTypes_namedarray_multidimarray_t;
				break;
			}
		}

		if (e->ElementFlags & MessageElementFlags_ELEMENT_NAME_STR)
		{			
			e->ElementName = MessageSerializationTest4_NewRandomString(rng, 128);
			e->ElementFlags &= ~MessageElementFlags_ELEMENT_NUMBER;
		}

		if (e->ElementFlags & MessageElementFlags_ELEMENT_NAME_CODE)
		{
			e->ElementNameCode = uint32_dist(rng);
			e->ElementFlags &= ~MessageElementFlags_ELEMENT_NUMBER;
		}

		if (e->ElementFlags & MessageElementFlags_ELEMENT_NUMBER)
		{
			e->ElementNumber = int32_dist(rng);
		}

		if (e->ElementFlags & MessageElementFlags_ELEMENT_TYPE_NAME_STR)
		{			
			e->ElementTypeName = MessageSerializationTest4_NewRandomString(rng, 128);
		}

		if (e->ElementFlags & MessageElementFlags_ELEMENT_TYPE_NAME_CODE)
		{
			e->ElementTypeNameCode = uint32_dist(rng);
		}

		if (e->ElementFlags & MessageElementFlags_META_INFO)
		{			
			e->MetaData = MessageSerializationTest4_NewRandomString(rng, 128);			
		}

		if (e->ElementFlags & MessageElementFlags_EXTENDED)
		{
			e->Extended = MessageSerializationTest4_NewRandomExtended(rng, 32);
		}

		switch (e->ElementType)
		{
		case DataTypes_void_t:
			return e;
		
		case DataTypes_double_t:
		case DataTypes_single_t:
		case DataTypes_int8_t:
		case DataTypes_uint8_t:
		case DataTypes_int16_t:
		case DataTypes_uint16_t:
		case DataTypes_int32_t:
		case DataTypes_uint32_t:
		case DataTypes_int64_t:
		case DataTypes_uint64_t:
		case DataTypes_string_t:
		{
			RR_INTRUSIVE_PTR<RRBaseArray> a = AllocateRRArrayByType(e->ElementType, len_dist(rng));
			uint8_t* a2 = (uint8_t*)a->void_ptr();
			for (size_t i = 0; i < a->ElementSize() * a->size(); i++)
			{
				a2[i] = uint8_dist(rng);
			}
			e->SetData(a);
			return e;
		}
		case DataTypes_structure_t:
		{
			std::vector<RR_INTRUSIVE_PTR<MessageElement> > v;
			size_t n = len_sub_dist(rng);
			for (size_t i = 0; i < n; i++)
			{
				v.push_back(MessageSerializationTest4_NewRandomMessageElement(rng, depth + 1));
			}
			e->SetData(CreateMessageElementNestedElementList(DataTypes_structure_t,MessageSerializationTest4_NewRandomString(rng, 128),v));
			return e;
		}
		case DataTypes_vector_t:
		{
			std::vector<RR_INTRUSIVE_PTR<MessageElement> > v;
			size_t n = len_sub_dist(rng);
			for (size_t i = 0; i < n; i++)
			{
				v.push_back(MessageSerializationTest4_NewRandomMessageElement(rng, depth + 1));
			}
			e->SetData(CreateMessageElementNestedElementList(DataTypes_vector_t,"",v));
			return e;
		}
		case DataTypes_dictionary_t:
		{
			std::vector<RR_INTRUSIVE_PTR<MessageElement> > v;
			size_t n = len_sub_dist(rng);
			for (size_t i = 0; i < n; i++)
			{
				v.push_back(MessageSerializationTest4_NewRandomMessageElement(rng, depth + 1));
			}
			e->SetData(CreateMessageElementNestedElementList(DataTypes_dictionary_t,"",v));
			return e;
		}
		case DataTypes_multidimarray_t:
		{
			std::vector<RR_INTRUSIVE_PTR<MessageElement> > v;
			size_t n = len_sub_dist(rng);
			if (n > 4) n = 4;
			for (size_t i = 0; i < n; i++)
			{
				v.push_back(MessageSerializationTest4_NewRandomMessageElement(rng, 10));
			}
			e->SetData(CreateMessageElementNestedElementList(DataTypes_multidimarray_t,"",v));
			return e;
		}
		case DataTypes_list_t:
		{
			std::vector<RR_INTRUSIVE_PTR<MessageElement> > v;
			size_t n = len_sub_dist(rng);
			for (size_t i = 0; i < n; i++)
			{
				v.push_back(MessageSerializationTest4_NewRandomMessageElement(rng, depth + 1));
			}
			e->SetData(CreateMessageElementNestedElementList(DataTypes_list_t,"",v));
			return e;
		}

		case DataTypes_pod_t:
		{
			std::vector<RR_INTRUSIVE_PTR<MessageElement> > v;
			size_t n = len_sub_dist(rng);
			for (size_t i = 0; i < n; i++)
			{
				v.push_back(MessageSerializationTest4_NewRandomMessageElement(rng, depth + 1));
			}
			e->SetData(CreateMessageElementNestedElementList(DataTypes_pod_t, "", v));
			return e;
		}
		case DataTypes_pod_array_t:
		{
			std::vector<RR_INTRUSIVE_PTR<MessageElement> > v;
			size_t n = len_sub_dist(rng);
			for (size_t i = 0; i < n; i++)
			{
				v.push_back(MessageSerializationTest4_NewRandomMessageElement(rng, depth + 1));
			}
			e->SetData(CreateMessageElementNestedElementList(DataTypes_pod_array_t,MessageSerializationTest4_NewRandomString(rng, 128),v));
			return e;
		}
		case DataTypes_pod_multidimarray_t:
		{
			std::vector<RR_INTRUSIVE_PTR<MessageElement> > v;
			size_t n = len_sub_dist(rng);
			for (size_t i = 0; i < n; i++)
			{
				v.push_back(MessageSerializationTest4_NewRandomMessageElement(rng, depth + 1));
			}
			e->SetData(CreateMessageElementNestedElementList(DataTypes_pod_multidimarray_t,MessageSerializationTest4_NewRandomString(rng, 128),v));
			return e;
		}
		case DataTypes_namedarray_array_t:
		{
			std::vector<RR_INTRUSIVE_PTR<MessageElement> > v;
			size_t n = len_sub_dist(rng);
			for (size_t i = 0; i < n; i++)
			{
				v.push_back(MessageSerializationTest4_NewRandomMessageElement(rng, depth + 1));
			}
			e->SetData(CreateMessageElementNestedElementList(DataTypes_namedarray_array_t,MessageSerializationTest4_NewRandomString(rng, 128), v));
			return e;
		}
		case DataTypes_namedarray_multidimarray_t:
		{
			std::vector<RR_INTRUSIVE_PTR<MessageElement> > v;
			size_t n = len_sub_dist(rng);
			for (size_t i = 0; i < n; i++)
			{
				v.push_back(MessageSerializationTest4_NewRandomMessageElement(rng, depth + 1));
			}
			e->SetData(CreateMessageElementNestedElementList(DataTypes_namedarray_multidimarray_t,MessageSerializationTest4_NewRandomString(rng, 128), v));
			return e;
		}
		default:
			throw std::runtime_error("Invalid random type");
		}
	}

	RR_INTRUSIVE_PTR<Message> MessageSerializationTest4::NewRandomTestMessage4(boost::random::mt19937& rng)
	{
		uniform_int_distribution<uint8_t>  uint8_dist;
		uniform_int_distribution<uint16_t> uint16_dist;
		uniform_int_distribution<uint32_t> uint32_dist;
		uniform_int_distribution<size_t> small_dist(1, 4);
		uniform_int_distribution<int32_t> int32_dist;
		uniform_int_distribution<int64_t> int64_dist;
		uniform_int_distribution<uint64_t> uint64_dist;

		RR_INTRUSIVE_PTR<Message> m = CreateMessage();
		RR_INTRUSIVE_PTR<MessageHeader> h = CreateMessageHeader();
		m->header = h;
		h->MessageFlags = MessageSerializationTest4_NewRandomMessageFlags(rng);
		/*h->MessageFlags &= ~MessageFlags_ROUTING_INFO;
		h->MessageFlags &= ~MessageFlags_ENDPOINT_INFO;
		h->MessageFlags &= ~MessageFlags_PRIORITY;
		h->MessageFlags &= ~MessageFlags_META_INFO;
		h->MessageFlags &= ~MessageFlags_STRING_TABLE;
		h->MessageFlags &= ~MessageFlags_EXTENDED;*/
		if (h->MessageFlags & MessageFlags_PRIORITY)
		{
			h->Priority = uint16_dist(rng);			
		}
		if (h->MessageFlags & MessageFlags_ROUTING_INFO)
		{
			boost::array < uint8_t, 16> b;
			for (size_t i = 0; i < 16; i++) b[i] = uint8_dist(rng);
			h->SenderNodeID = NodeID(b);
			for (size_t i = 0; i < 16; i++) b[i] = uint8_dist(rng);
			h->ReceiverNodeID = NodeID(b);
			h->SenderNodeName = MessageSerializationTest4_NewRandomString(rng, 64);
			h->ReceiverNodeName = MessageSerializationTest4_NewRandomString(rng, 64);
		}

		if (h->MessageFlags & MessageFlags_ENDPOINT_INFO)
		{
			h->SenderEndpoint = uint32_dist(rng);
			h->ReceiverEndpoint = uint32_dist(rng);
		}

		if (h->MessageFlags & MessageFlags_META_INFO)
		{
			h->MetaData = MessageSerializationTest4_NewRandomString(rng, 256);
			h->MessageID = uint16_dist(rng);
			h->MessageResID = uint16_dist(rng);
		}

		if (h->MessageFlags & MessageFlags_STRING_TABLE)
		{
			size_t n = small_dist(rng);
			for (size_t i = 0; i < n; i++)
			{
				h->StringTable.push_back(boost::make_tuple(uint32_dist(rng), MessageSerializationTest4_NewRandomString(rng, 128)));
			}
		}

		if (h->MessageFlags & MessageFlags_MULTIPLE_ENTRIES)
		{
			h->EntryCount = (int16_t)small_dist(rng);
		}
		else
		{
			h->EntryCount = 1;
		}

		if (h->MessageFlags & MessageFlags_EXTENDED)
		{
			h->Extended = MessageSerializationTest4_NewRandomExtended(rng, 32);			
		}

		//Add a large entry sometimes
		uint32_t add_large_entry = small_dist(rng);

		for (size_t i = 0; i < h->EntryCount; i++)
		{
			if (m->ComputeSize4() > 10 * 1024 * 1024) break;

			RR_INTRUSIVE_PTR<MessageEntry> ee = CreateMessageEntry();

			ee->EntryFlags = MessageSerializationTest4_NewRandomFlags(rng);
			
			uniform_int_distribution<uint16_t> entry_type_dist(101, 120);
			ee->EntryType = (MessageEntryType)entry_type_dist(rng);

			if (ee->EntryFlags & MessageEntryFlags_SERVICE_PATH_STR)
			{				
				ee->ServicePath = MessageSerializationTest4_NewRandomString(rng, 256);
			}
			if (ee->EntryFlags & MessageEntryFlags_SERVICE_PATH_CODE)
			{				
				ee->ServicePathCode = uint32_dist(rng);
			}
			if (ee->EntryFlags & MessageEntryFlags_MEMBER_NAME_STR)
			{				
				ee->MemberName = MessageSerializationTest4_NewRandomString(rng, 256);
			}
			if (ee->EntryFlags & MessageEntryFlags_MEMBER_NAME_CODE)
			{				
				ee->MemberNameCode = uint32_dist(rng);
			}
			
			if (ee->EntryFlags & MessageEntryFlags_REQUEST_ID)
			{
				ee->RequestID = uint32_dist(rng);
			}
			if (ee->EntryFlags & MessageEntryFlags_ERROR)
			{
				uniform_int_distribution<uint16_t> error_dist(1, 10);
				ee->Error = (MessageErrorType)error_dist(rng);
			}
			if (ee->EntryFlags & MessageEntryFlags_META_INFO)
			{				
				ee->MetaData = MessageSerializationTest4_NewRandomString(rng, 256);
			}
			
			if (ee->EntryFlags & MessageFlags_EXTENDED)
			{
				ee->Extended = MessageSerializationTest4_NewRandomExtended(rng, 32);
			}
			
			if (add_large_entry == 1 && i == 0)
			{
				uniform_int_distribution<size_t> large_len_dist(512 * 1024, 1024 * 1024);
				size_t l = large_len_dist(rng);
				RR_INTRUSIVE_PTR<RRArray<uint32_t> > a = AllocateRRArray<uint32_t>(l);
				uint32_t* a2 = a->data();
				for (size_t j = 0; j < l; j++)
				{
					a2[j] = uint32_dist(rng);
				}

				RR_INTRUSIVE_PTR<MessageElement> el = MessageSerializationTest4_NewRandomMessageElement(rng, 10);
				el->SetData(a);
				ee->elements.push_back(el);
			}
			else
			{
				uniform_int_distribution<size_t> el_count_dist(0, 16);
				size_t n1 = el_count_dist(rng);
				for (size_t j = 0; j < n1; j++)
				{
					RR_INTRUSIVE_PTR<MessageElement> el= MessageSerializationTest4_NewRandomMessageElement(rng, 0);
					ee->elements.push_back(el);
				}
			}

			m->entries.push_back(ee);
		}
				
		return m;
	}

	void MessageSerializationTest4::Test()
	{
		Test1();
		Test2(false);
		Test2(true);
		Test3();
	}

	void MessageSerializationTest4::Test1()
	{
		RR_INTRUSIVE_PTR<Message> m = MessageSerializationTest::NewTestMessage();

		//Write to stream and read back
		size_t message_size=m->ComputeSize4();
		boost::shared_array<uint8_t> buf(new uint8_t[message_size]);
		ArrayBinaryWriter w(buf.get(),0,message_size); 
		m->Write4(w);

		if (w.Position() != m->ComputeSize4())
			throw std::runtime_error("");

		ArrayBinaryReader r(buf.get(),0,message_size);

		RR_INTRUSIVE_PTR<Message> m2 = CreateMessage();
		m2->Read4(r);

		MessageSerializationTest::CompareMessage(m, m2);
	}

	void MessageSerializationTest4::Test2(bool use_string_table)
	{
		RR_INTRUSIVE_PTR<Message> m= MessageSerializationTest::NewTestMessage();

		RR_SHARED_PTR<RobotRaconteur::detail::StringTable> string_table1 = RR_MAKE_SHARED<RobotRaconteur::detail::StringTable>(false);
		if (use_string_table)
		{
			
			string_table1->MessageReplaceStringsWithCodes(m);
		}
		
		//Write to stream and read back
		size_t message_size = m->ComputeSize4();
		boost::shared_array<uint8_t> buf(new uint8_t[message_size]);
		ArrayBinaryWriter w(buf.get(), 0, message_size);
		m->Write4(w);

		if (w.Position() != m->ComputeSize4())
			throw std::runtime_error("");

		ArrayBinaryReader r(buf.get(), 0, message_size);

		RR_INTRUSIVE_PTR<Message> m2 = CreateMessage();
		uint16_t version_minor;
		m2->Read4(r);		

		if (use_string_table)
		{
			RR_SHARED_PTR<RobotRaconteur::detail::StringTable> string_table2 = RR_MAKE_SHARED<RobotRaconteur::detail::StringTable>(false);
			string_table2->MessageReplaceCodesWithStrings(m2);
			string_table1->MessageReplaceCodesWithStrings(m);
		}

		MessageSerializationTest::CompareMessage(m, m2);
	}

	void MessageSerializationTest4::Test3()
	{
		srand((uint32_t)time(NULL));
		
		RR_INTRUSIVE_PTR<MessageElement> e2 = CreateMessageElement();
		e2->ElementFlags &= MessageElementFlags_ELEMENT_NAME_STR;
		e2->ElementFlags |= MessageElementFlags_ELEMENT_NUMBER;
		e2->ElementNumber = 134576569;		

		RR_INTRUSIVE_PTR<MessageEntry> e1 = CreateMessageEntry(MessageEntryType_PropertyGetReq, "testprimitives");
		

		RR_INTRUSIVE_PTR<Message> m = CreateMessage();
		RR_INTRUSIVE_PTR<MessageHeader> h = CreateMessageHeader();
		h->MessageFlags = 0;

		m->header = h;
	
		h->MessageFlags = MessageFlags_UNRELIABLE;
		
		m->entries.push_back(e1);

		//Write to stream and read back
		size_t message_size = m->ComputeSize4();
		boost::shared_array<uint8_t> buf(new uint8_t[message_size]);
		ArrayBinaryWriter w(buf.get(), 0, message_size);
		m->Write4(w);

		if (w.Position() != m->ComputeSize4())
			throw std::runtime_error("");

		ArrayBinaryReader r(buf.get(), 0, message_size);

		RR_INTRUSIVE_PTR<Message> m2 = CreateMessage();
		uint16_t version_minor;
		m2->Read4(r);

		MessageSerializationTest::CompareMessage(m, m2);
	}

	void MessageSerializationTest4::RandomTest(size_t iterations)
	{
		mt19937 rng;
		rng.seed((uint32_t)std::time(0));

		for (size_t i = 0; i < iterations; i++)
		{
			RR_INTRUSIVE_PTR<Message> m = NewRandomTestMessage4(rng);

			//Write to stream and read back
			size_t message_size = m->ComputeSize4();
			boost::shared_array<uint8_t> buf(new uint8_t[message_size]);
			ArrayBinaryWriter w(buf.get(), 0, message_size);
			m->Write4(w);

			if (w.Position() != m->ComputeSize4())
				throw std::runtime_error("");

			ArrayBinaryReader r(buf.get(), 0, message_size);

			RR_INTRUSIVE_PTR<Message> m2 = CreateMessage();
			
			m2->Read4(r);

			MessageSerializationTest::CompareMessage(m, m2);
		}


	}

}
