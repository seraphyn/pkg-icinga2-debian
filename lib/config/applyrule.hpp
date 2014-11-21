/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2014 Icinga Development Team (http://www.icinga.org)    *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef APPLYRULE_H
#define APPLYRULE_H

#include "config/i2-config.hpp"
#include "config/expression.hpp"
#include "base/debuginfo.hpp"
#include <boost/function.hpp>

namespace icinga
{

/**
 * @ingroup config
 */
class I2_CONFIG_API ApplyRule
{
public:
	typedef boost::function<void (const std::vector<ApplyRule>& rules)> Callback;
	typedef std::map<String, std::pair<Callback, std::vector<String> > > CallbackMap;
	typedef std::map<String, std::vector<ApplyRule> > RuleMap;

	String GetTargetType(void) const;
	String GetName(void) const;
	boost::shared_ptr<Expression> GetExpression(void) const;
	boost::shared_ptr<Expression> GetFilter(void) const;
	String GetFKVar(void) const;
	String GetFVVar(void) const;
	boost::shared_ptr<Expression> GetFTerm(void) const;
	DebugInfo GetDebugInfo(void) const;
	Object::Ptr GetScope(void) const;

	bool EvaluateFilter(const Object::Ptr& scope) const;

	static void AddRule(const String& sourceType, const String& targetType, const String& name, const boost::shared_ptr<Expression>& expression,
	    const boost::shared_ptr<Expression>& filter, const String& fkvar, const String& fvvar, const boost::shared_ptr<Expression>& fterm, const DebugInfo& di, const Object::Ptr& scope);
	static void EvaluateRules(bool clear);

	static void RegisterType(const String& sourceType, const std::vector<String>& targetTypes, const ApplyRule::Callback& callback);
	static bool IsValidSourceType(const String& sourceType);
	static bool IsValidTargetType(const String& sourceType, const String& targetType);
	static std::vector<String> GetTargetTypes(const String& sourceType);

private:
	String m_TargetType;
	String m_Name;
	boost::shared_ptr<Expression> m_Expression;
	boost::shared_ptr<Expression> m_Filter;
	String m_FKVar;
	String m_FVVar;
	boost::shared_ptr<Expression> m_FTerm;
	DebugInfo m_DebugInfo;
	Object::Ptr m_Scope;

	static CallbackMap m_Callbacks;
	static RuleMap m_Rules;

	ApplyRule(const String& targetType, const String& name, const boost::shared_ptr<Expression>& expression,
	    const boost::shared_ptr<Expression>& filter, const String& fkvar, const String& fvvar, const boost::shared_ptr<Expression>& fterm,
	    const DebugInfo& di, const Object::Ptr& scope);
};

}

#endif /* APPLYRULE_H */
