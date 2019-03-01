inherit SKILL;
void create() { seteuid(getuid()); }
string type() { return "knowledge"; }
int practice_skill(object me)
{   
        return notify_fail("煉丹術只能通過學習(learn)，或者在實踐中提高!\n");
}