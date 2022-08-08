#ifndef HTTPBLOCK_HPP
#define HTTPBLOCK_HPP

#include "BaseDirectives.hpp"
#include "ServerBlock.hpp"

namespace ft
{
	class ServerBlock;
	class HttpBlock : public BaseDirectives
	{
		public:
			std::vector<ServerBlock>	server_list;
		public:
			HttpBlock();
			HttpBlock(const HttpBlock& other);
			HttpBlock& operator= (const HttpBlock& other);
			~HttpBlock();
			std::vector<ServerBlock>	getServerBlock() const;
	};

}

#endif
