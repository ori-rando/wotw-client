#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <variant>

namespace randomizer::seed {
    enum class SourceStatus {
        Loading,
        Ready,
        Error,
    };

    class SeedSource {
    public:
        virtual ~SeedSource() = default;

        /** Poll the status of this seed source, and if it's ready, the seed content */
        virtual std::pair<SourceStatus, std::optional<std::string>> poll() = 0;

        /** The human description of this seed source */
        virtual std::string get_description() = 0;

        /** Convert this seed source to a source string. This must be the inverse of parse_source_string */
        virtual std::string to_source_string() = 0;

        /** The multiverse ID to connect to, or nullopt if no server connection should be made */
        virtual std::optional<long> get_multiverse_id() = 0;

        /** Reread the seed source */
        virtual bool allows_rereading() = 0;

        /** Query custom properties for seed sources */
        std::optional<std::variant<std::string, int, float>> get_property(int property) {
            return std::nullopt;
        }

        std::optional<std::string> get_error() { return m_error; }

    protected:
        std::optional<std::string> m_error;
    };

    class FileSeedSource: public SeedSource {
    public:
        std::pair<SourceStatus, std::optional<std::string>> poll() override;
        std::string get_description() override;
        std::string to_source_string() override;
        std::optional<long> get_multiverse_id() override;
        bool allows_rereading() override;

        explicit FileSeedSource(const std::filesystem::path& path);

    private:
        std::filesystem::path m_path;
        std::optional<std::string> m_content;
    };

    class DebugDelayedFileSeedSource: public SeedSource {
    public:
        std::pair<SourceStatus, std::optional<std::string>> poll() override;
        std::string get_description() override;
        std::string to_source_string() override;
        std::optional<long> get_multiverse_id() override;
        bool allows_rereading() override;

        explicit DebugDelayedFileSeedSource(const std::filesystem::path& path);

    private:
        bool loaded = false;
        std::filesystem::path m_path;
        std::optional<std::string> m_content;
    };

    class ServerSeedSource: public SeedSource {
    public:
        std::pair<SourceStatus, std::optional<std::string>> poll() override;
        std::string get_description() override;
        std::string to_source_string() override;
        std::optional<long> get_multiverse_id() override;
        bool allows_rereading() override;

        explicit ServerSeedSource(long multiverse_id) : m_multiverse_id(multiverse_id) {};

    private:
        long m_multiverse_id;
    };

    class ArchipelagoSeedSource: public SeedSource {
    public:
        std::pair<SourceStatus, std::optional<std::string>> poll() override;
        std::string get_description() override;
        std::string to_source_string() override;
        std::optional<long> get_multiverse_id() override;
        bool allows_rereading() override;

        explicit ArchipelagoSeedSource(const std::string host, const int port, const std::string password);

    private:
        std::filesystem::path m_path;
        std::optional<std::string> m_content;
    };

    class EmptySeedSource: public SeedSource {
    public:
        std::pair<SourceStatus, std::optional<std::string>> poll() override;
        std::string get_description() override;
        std::string to_source_string() override;
        std::optional<long> get_multiverse_id() override;
        bool allows_rereading() override;
    };

    class InvalidSeedSource: public SeedSource {
    public:
        std::pair<SourceStatus, std::optional<std::string>> poll() override;
        std::string get_description() override;
        std::string to_source_string() override;
        std::optional<long> get_multiverse_id() override;
        bool allows_rereading() override;

        explicit InvalidSeedSource(const std::string& source_string) : m_source_string(source_string) {
            m_error = std::format("Invalid source: {}", source_string);
        };

    private:
        std::string m_source_string;
    };

    void set_server_seed_content(const std::optional<std::string>& content);
    std::shared_ptr<SeedSource> parse_source_string(const std::string& source);
}
