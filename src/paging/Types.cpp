#include "paging/Types.h"

double Stats::tlb_miss_rate() const noexcept {
    if (total_accesses == 0) {
        return 0.0;
    }
    return static_cast<double>(tlb_misses) / static_cast<double>(total_accesses);
}

double Stats::page_fault_rate() const noexcept {
    if (total_accesses == 0) {
        return 0.0;
    }
    return static_cast<double>(page_faults) / static_cast<double>(total_accesses);
}
