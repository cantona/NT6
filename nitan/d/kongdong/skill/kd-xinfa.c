// kongdong xinfa.c

inherit FORCE;

string query_xiuwei_type() { return "force"; }

int practice_skill(object me)
{
	return notify_fail("崆峒心法只能用學的，或是從運用(exert)中增加熟練度。\n");
}

int valid_xiulian( object me ) { return 1; }

int query_level() { return 2; }
string query_type() { return "yin"; }
