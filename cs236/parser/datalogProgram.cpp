// Written by Aleks Christensen

#include "datalogProgram.h"

datalogProgram::datalogProgram(){}

datalogProgram::~datalogProgram(){}

string datalogProgram::parse(vector<Token> tokens)
{
    vt = tokens;
    try {
        match("SCHEMES");
        match("COLON");
        scheme();
        schemeList();
        match("FACTS");
        match("COLON");
        factList();
        match("RULES");
        match("COLON");
        ruleList();
        match("QUERIES");
        match("COLON");
        query();
        queryList();
        match("EOF");
    } catch (Token t) {
        ostringstream o;
        o << "Failure!\n";
        o << "  (" << t.type << ",\"" << t.content << "\"," << t.line << ")" << endl;
        return o.str();
    }
    return toString();
}

void datalogProgram::scheme()
{
    match("ID");
    Predicate p;
    p.id = vt.at(index-1).content;
    match("LEFT_PAREN");
    match("ID");
    vector<Param> parms;
    parms.push_back(Param(vt.at(index-1).content, true, false));
    idList(parms);
    match("RIGHT_PAREN");
    p.params = parms;
    schemes.push_back(p);
}

void datalogProgram::schemeList()
{
    if (vt.at(index).type != "FACTS") { scheme(); schemeList(); }
}

void datalogProgram::idList(vector<Param> &parms)
{
    if (vt.at(index).type == "COMMA") {
        match("COMMA");
        match("ID");
        parms.push_back(Param(vt.at(index-1).content, true, false));
        idList(parms);
    }
}

void datalogProgram::fact()
{
    match("ID");
    Predicate p;
    p.id = vt.at(index-1).content;
    match("LEFT_PAREN");
    match("STRING");
    vector<Param> parms;
    parms.push_back(Param(vt.at(index-1).content, false, true));
    stringList(parms);
    match("RIGHT_PAREN");
    match("PERIOD");
    p.params = parms;
    facts.push_back(p);
}

void datalogProgram::factList()
{
    if (vt.at(index).type != "RULES") { fact(); factList(); }
}

void datalogProgram::rule()
{
    Rule r;
    r.head = headPredicate();
    match("COLON_DASH");
    r.rules.push_back(predicate());
    predicateList(r.rules);
    match("PERIOD");
    rules.push_back(r);
}

void datalogProgram::ruleList()
{
    if (vt.at(index).type != "QUERIES") { rule(); ruleList(); }
}

Predicate datalogProgram::headPredicate()
{
    match("ID");
    Predicate p;
    p.id = vt.at(index-1).content;
    match("LEFT_PAREN");
    match("ID");
    vector<Param> parms;
    parms.push_back(Param(vt.at(index-1).content, true, false));
    idList(parms);
    match("RIGHT_PAREN");
    p.params = parms;
    return p;
}

Predicate datalogProgram::predicate()
{
    match("ID");
    Predicate p;
    p.id = vt.at(index-1).content;
    match("LEFT_PAREN");
    vector<Param> parms;
    parms.push_back(parameter());
    parameterList(parms);
    match("RIGHT_PAREN");
    p.params = parms;
    return p;
}

void datalogProgram::predicateList(vector<Predicate> &rules)
{
    if (vt.at(index).type == "COMMA") {
        match("COMMA");
        rules.push_back(predicate());
        predicateList(rules);
    }
}

Param datalogProgram::parameter()
{
    if (vt.at(index).type == "STRING") {
        index++;
        return Param(vt.at(index-1).content, false, true);
    }
    else if (vt.at(index).type == "ID") {
        index++;
        return Param(vt.at(index-1).content, true, false);
    }
    else return expression();
}

void datalogProgram::parameterList(vector<Param> &parms)
{
    if (vt.at(index).type == "COMMA") {
        match("COMMA");
        parms.push_back(parameter());
        parameterList(parms);
    }
}

Param datalogProgram::expression()
{
    match("LEFT_PAREN");
    string expr;
    expr.append("(");
    expr.append(parameter().value);
    expr.append(op());
    expr.append(parameter().value);
    expr.append(")");
    match("RIGHT_PAREN");
    return Param(expr, false, false);
}

string datalogProgram::op()
{
    if (vt.at(index).type == "ADD") {
        index++;
        return "+";
    }
    else {
        index++;
        return "*";
    }
}

void datalogProgram::query()
{
    Predicate p = predicate();
    match("Q_MARK");
    queries.push_back(p);
}

void datalogProgram::queryList()
{
    if (vt.at(index).type != "EOF") { query(); queryList(); }
}

void datalogProgram::stringList(vector<Param> &parms)
{
    if (vt.at(index).type == "COMMA") {
        match("COMMA");
        match("STRING");
        parms.push_back(Param(vt.at(index-1).content, false, true));
        stringList(parms);
    }
}

void datalogProgram::match(string type)
{
    if (vt.at(index).type == type) ++index;
    else throw vt.at(index);
}

vector<string> datalogProgram::domain()
{
    vector<string> dv;
    string t;
    for (size_t f = 0; f < facts.size(); ++f) {
        for (size_t p = 0; p < facts.at(f).params.size(); ++p) {
            if (facts.at(f).params.at(p).isString) t = facts.at(f).params.at(p).toString();
            if (!isIn(dv, t)) dv.push_back(t);
        }
    }
    return dv;
}

bool datalogProgram::isIn(vector<string> dv, string s)
{
    for (size_t i = 0; i < dv.size(); ++i) {
        if (dv.at(i) == s) return true;
    }
    return false;
}

string datalogProgram::schemesToString()
{
    ostringstream out;
    out << "Schemes(" << schemes.size() << "):" << endl;
    for (size_t i = 0; i < schemes.size(); ++i) {
        out << "  " << schemes.at(i).toString() << endl;
    }
    return out.str();
}

string datalogProgram::factsToString()
{
    ostringstream out;
    out << "Facts(" << facts.size() << "):" << endl;
    for (size_t i = 0; i < facts.size(); ++i) {
        out << "  " << facts.at(i).toString() << "." << endl;
    }
    return out.str();
}

string datalogProgram::rulesToString()
{
    ostringstream out;
    out << "Rules(" << rules.size() << "):" << endl;
    for (size_t i = 0; i < rules.size(); ++i) {
        out << "  " << rules.at(i).toString() << endl;
    }
    return out.str();
}

string datalogProgram::queriesToString()
{
    ostringstream out;
    out << "Queries(" << queries.size() << "):" << endl;
    for (size_t i = 0; i < queries.size(); ++i) {
        out << "  " << queries.at(i).toString() << "?" << endl;
    }
    return out.str();
}

string datalogProgram::domainToString(vector<string> dv)
{
    ostringstream out;
    out << "Domain(" << dv.size() << "):" << endl;
    for (size_t i = 0; i < dv.size(); ++i) {
        out << "  " << dv.at(i) << endl;
    }
    return out.str();
}

string datalogProgram::toString()
{
    ostringstream out;
    vector<string> dv = domain();
    sort(dv.begin(), dv.end());

    out << "Success!" << endl;
    out << schemesToString();
    out << factsToString();
    out << rulesToString();
    out << queriesToString();
    out << domainToString(dv);

    return out.str();
}
