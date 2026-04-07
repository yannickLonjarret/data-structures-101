#include <stdio.h>
#include <stdlib.h>

#include "PatientIndexer.h"

// Data structure creation and deletion
IndexerManager CreateIndexerManager(int numberOfIndexers) {
    IndexerManager manager;
    manager.indexerCount = numberOfIndexers;
    manager.indexers = (PatientIndexer*)malloc(sizeof(PatientIndexer) * numberOfIndexers);

    if(manager.indexers == NULL) {
        fprintf(stderr, "Malloc issue when creating the manager indexer.");
        abort();
    }

    return manager;
}
