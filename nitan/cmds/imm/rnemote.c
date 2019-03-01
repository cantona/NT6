// rnemote.c
// create by doing

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string from, to;
        mapping emote;
        mapping toemote;
        int i;
        string *ks;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(getuid());

        if (! VERSION_D->is_release_server())
                return notify_fail("只有版本發布站點才能修改表情動詞。\n");

        if (! arg || sscanf(arg, "%s %s", from, to) != 2)
                return help(me);

        emote = EMOTE_D->query_emote(from);
        if (! emote || ! sizeof(emote))
                return notify_fail("沒有(" + from + ")這個表情動詞。\n");

        if ((toemote = EMOTE_D->query_emote(to)) && sizeof(toemote))
                return notify_fail("表情動詞(" + to + ")已經存在，不能改成該名字。\n");

        EMOTE_D->set_emote(to, emote);
        EMOTE_D->delete_emote(from);
        write(sprintf("表情動詞(%s)改名為(%s)。\n", from, to));
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : rnemote <from> <to>

改命令將原名為 <from> 的 emote 改成名字為 <to> 的新 emote。
注意：原先必須不能存在名為 <to> 的表情動詞。

由于表情動詞會在版本同步時更新，因此只有版本發布站點才能夠使
用這個命令。

see also：edemote、cpemote
HELP );
        return 1;
}