#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <memory>
#include <map>

class DataConfig{
public:
    std::string resource_;
    std::string config_;
    std::string rule_;
};

class ConfigStore{
public:
    std::map<std::string, DataConfig> store; // resource_rule , config

};

class Rule{
public:
    virtual void doMessage() = 0;

    std::map<std::string, DataConfig> config;
};

class ParsingRule : public Rule{
public:

    void doMessage() override {
        std::cout << "parsing-rule" << std::endl;
    }
};

class RoutingRule : public Rule{
public:
    void doMessage() override {
        std::cout << "routing-rule" << std::endl;
    }
};




int main() {
    using RulePtr = std::shared_ptr<Rule>;
    std::vector<RulePtr> ruleList;


    DataConfig config1;
    config1.resource_ = "resource1";
    config1.rule_ = "rule1";
    config1.config_ = "data1";

    DataConfig config2;
    config2.resource_ = "resource2";
    config2.rule_ = "rule2";
    config2.config_ = "data2";

    ConfigStore configStore;
    configStore.store.insert({config1.resource_ + config1.rule_, config1});
    configStore.store.insert({config2.resource_ + config2.rule_, config2});


    auto parsingRule = std::make_shared<ParsingRule>();
    parsingRule->config.insert({config1.resource_, config1});

    auto routingRule = std::make_shared<RoutingRule>();
    routingRule->config.insert({config2.resource_, config2});

    ruleList.push_back(parsingRule);
    ruleList.push_back(routingRule);




    for(auto& rule : ruleList){
        rule->doMessage();

        for(const auto& config : rule->config){
            std::cout << config.second.config_ << std::endl;
        }

    }

    return 0;
}