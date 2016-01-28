/* Copyright (C) 2015 Alexander Shishenko <GamePad64@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "../pch.h"
#pragma once
#include "../util/Loggable.h"
#include "AbstractFolder.h"
#include "../util/AvailabilityMap.h"

namespace librevault {

class Client;
class RemoteDirectory;
class FolderGroup;

class Uploader : public std::enable_shared_from_this<Uploader>, protected Loggable {
public:
	Uploader(Client& client, FolderGroup& exchange_group);

	void handle_interested(std::shared_ptr<RemoteDirectory> remote);
	void handle_not_interested(std::shared_ptr<RemoteDirectory> remote);

	void request_chunk(std::shared_ptr<RemoteDirectory> origin, const blob& encrypted_data_hash, uint32_t offset, uint32_t size);

private:
	Client& client_;
	FolderGroup& exchange_group_;
};

} /* namespace librevault */