/*
 * TesterKeyValueStore.h
 *
 * This source file is part of the FoundationDB open source project
 *
 * Copyright 2013-2022 Apple Inc. and the FoundationDB project authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#ifndef APITESTER_KEY_VALUE_STORE_H
#define APITESTER_KEY_VALUE_STORE_H

#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <mutex>

#include "TesterUtil.h"

namespace FdbApiTester {

class KeyValueStore {
public:
	// Get the value associated with a key
	std::optional<fdb::Value> get(fdb::KeyRef key) const;

	// Checks if the key exists
	bool exists(fdb::KeyRef key);

	// Returns the key designated by a key selector
	fdb::Key getKey(fdb::KeyRef keyName, bool orEqual, int offset) const;

	// Gets a range of key-value pairs, returning a maximum of <limit> results
	std::vector<fdb::KeyValue> getRange(fdb::KeyRef begin, fdb::KeyRef end, int limit, bool reverse) const;

	// Stores a key-value pair in the database
	void set(fdb::KeyRef key, fdb::ValueRef value);

	// Removes a key from the database
	void clear(fdb::KeyRef key);

	// Removes a range of keys from the database
	void clear(fdb::KeyRef begin, fdb::KeyRef end);

	// The number of keys in the database
	uint64_t size() const;

	// The first key in the database; returned by key selectors that choose a key off the front
	fdb::Key startKey() const;

	// The last key in the database; returned by key selectors that choose a key off the back
	fdb::Key endKey() const;

	// Debugging function that prints all key-value pairs
	void printContents() const;

private:
	// A map holding the key-value pairs
	std::map<fdb::Key, fdb::Value, std::less<>> store;
	mutable std::mutex mutex;
};

} // namespace FdbApiTester

#endif
