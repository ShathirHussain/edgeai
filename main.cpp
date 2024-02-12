#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <vector>


struct Address {
    std::string city;
    std::string country;
};

struct Person {
    std::string name;
    int age;
    std::vector<std::string> hobbies;
    Address address;
};


void saveObjectToYAML(const Person& person, const std::string& filename) {
    try {
        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "name" << YAML::Value << person.name;
        emitter << YAML::Key << "age" << YAML::Value << person.age;
        emitter << YAML::Key << "hobbies" << YAML::Value << YAML::BeginSeq;
        for (const auto& hobby : person.hobbies) {
            emitter << hobby;
        }
        emitter << YAML::EndSeq;
        emitter << YAML::Key << "address" << YAML::Value << YAML::BeginMap;
        emitter << YAML::Key << "city" << YAML::Value << person.address.city;
        emitter << YAML::Key << "country" << YAML::Value << person.address.country;
        emitter << YAML::EndMap;
        emitter << YAML::EndMap;

        // Write YAML to file
        std::ofstream outFile(filename);
        outFile << emitter.c_str();
        std::cout << "YAML file created successfully: " << filename << std::endl;
    } catch (const YAML::Exception& e) {
        std::cerr << "Error creating YAML file: " << e.what() << std::endl;
    }
}

Person loadObjectFromYAML(const std::string& filename) {
    try {
        YAML::Node yamlNode = YAML::LoadFile(filename);

        // Extracting values from the YAML document
        Person person;
        person.name = yamlNode["name"].as<std::string>();
        person.age = yamlNode["age"].as<int>();

        const YAML::Node& hobbiesNode = yamlNode["hobbies"];
        for (const auto& hobby : hobbiesNode) {
            person.hobbies.push_back(hobby.as<std::string>());
        }

        const YAML::Node& addressNode = yamlNode["address"];
        person.address.city = addressNode["city"].as<std::string>();
        person.address.country = addressNode["country"].as<std::string>();

        return person;
    } catch (const YAML::Exception& e) {
        std::cerr << "Error parsing YAML file: " << e.what() << std::endl;

        return Person();
    }
}


void parseYAML(const YAML::Node& node, const std::string& indent = "") {
    if (node.IsMap()) {
        for (const auto& pair : node) {
            std::cout << indent << pair.first.as<std::string>() << ":" << std::endl;
            parseYAML(pair.second, indent + "  ");
        }
    } else if (node.IsSequence()) {
        for (const auto& element : node) {
            parseYAML(element, indent + "  ");
        }
    } else {
        std::cout << indent << node.as<std::string>() << std::endl;
    }
}


int main() {
    // Example nested object
    Person johnDoe = {
            "John Doe",
            30,
            {"Reading", "Traveling", "Coding"},
            {"New York", "USA"}
    };

    // Save the nested object to a YAML file
    saveObjectToYAML(johnDoe, "/home/sr/Desktop/shathir/yamltest/output_nested.yaml");

//    try {
//        // Load YAML from a file
//        YAML::Node yamlNode = YAML::LoadFile("your_yaml_file.yaml");
//
//        // Parse the YAML document
//        parseYAML(yamlNode);
//    } catch (const YAML::Exception& e) {
//        std::cerr << "Error parsing YAML: " << e.what() << std::endl;
//    }

    Person loadedPerson = loadObjectFromYAML("/home/sr/Desktop/shathir/yamltest/output_nested.yaml");

//    // Display the loaded object
    std::cout << "Loaded Person:" << std::endl;
    std::cout << "Name: " << loadedPerson.name << std::endl;
    std::cout << "Age: " << loadedPerson.age << std::endl;
    std::cout << "Hobbies:" << std::endl;
    for (const auto& hobby : loadedPerson.hobbies) {
        std::cout << "- " << hobby << std::endl;
    }
    std::cout << "Address:" << std::endl;
    std::cout << "City: " << loadedPerson.address.city << std::endl;
    std::cout << "Country: " << loadedPerson.address.country << std::endl;

    return 0;
}