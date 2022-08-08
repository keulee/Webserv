#ifndef LOCATIONBLOCK_HPP
#define LOCATIONBLOCK_HPP

#include "BaseDirectives.hpp"

namespace ft
{
	class LocationBlock : public BaseDirectives
	{
		private:
			std::vector<std::string>	limitExcept_;
			std::vector<std::string>	return_;
			std::vector<std::string>	cgi_;
			std::string			cgiPath_;
		public:
			LocationBlock();
			LocationBlock(const BaseDirectives& context);
			LocationBlock(const LocationBlock& other);
			~LocationBlock();
			LocationBlock& operator= (const LocationBlock& other);
			// Getter
			const std::vector<std::string>	getLimitExcept(void) const;
			const std::vector<std::string>	getReturn(void) const;
			const std::vector<std::string>	getCgi(void) const;
			const std::string		getCgiPath(void) const;

			// Setter
			void				setLimitExcept(const std::vector<std::string> x);
			void				setLimitExcept(const std::string x);
			void				setReturn(const std::vector<std::string> x);
			void				setReturn(const std::string x);
			void				setCgi(const std::vector<std::string> x);
			void				setCgi(const std::string x);
			void				setCgiPath(const std::string x);
	};

}

#endif
