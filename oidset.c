#include "cache.h"
#include "oidset.h"

int oidset_contains(const struct oidset *set, const struct object_id *oid)
{
	khiter_t pos = kh_get_oid(&set->set, *oid);
	return pos != kh_end(&set->set);
}

int oidset_insert(struct oidset *set, const struct object_id *oid)
{
	int added;
	kh_put_oid(&set->set, *oid, &added);
	return !added;
}

int oidset_remove(struct oidset *set, const struct object_id *oid)
{
	khiter_t pos = kh_get_oid(&set->set, *oid);
	if (pos == kh_end(&set->set))
		return 0;
	kh_del_oid(&set->set, pos);
	return 1;
}

void oidset_clear(struct oidset *set)
{
	kh_release_oid(&set->set);
	oidset_init(set, 0);
}
