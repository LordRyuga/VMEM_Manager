#pragma once

#include <cstdint>
#include <type_traits>

// ── Enumerations ───────────────────────────────────────────────────────────

enum class AccessType : uint8_t {
    READ,
    WRITE,
    EXEC
};

enum class AccessControl : uint8_t {
    READ_ONLY,
    READ_WRITE,
    EXEC_ONLY,
    NONE
};

// ── TLB entry ──────────────────────────────────────────────────────────────

struct TLBEntry {
    uint32_t      page_num  = 0;
    uint32_t      frame     = 0;
    AccessControl acl       = AccessControl::NONE;
    uint8_t       asid      = 0;
    bool          valid     = false;
    bool          dirty     = false;
};

// ── Page Table entry ───────────────────────────────────────────────────────

struct PageTableEntry {
    uint32_t      frame       = 0;
    AccessControl acl         = AccessControl::NONE;
    uint32_t      swap_offset = 0;
    bool          valid       = false;
    bool          dirty       = false;
};

// ── Simulation statistics ──────────────────────────────────────────────────

struct Stats {
    uint64_t total_accesses = 0;
    uint64_t tlb_hits       = 0;
    uint64_t tlb_misses     = 0;
    uint64_t page_faults    = 0;

    double tlb_miss_rate()   const noexcept;
    double page_fault_rate() const noexcept;
};

static_assert(std::is_trivially_copyable_v<TLBEntry>);
static_assert(std::is_trivially_copyable_v<PageTableEntry>);
