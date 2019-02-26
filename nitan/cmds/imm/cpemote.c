// cpemote.c
// created by doing

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
                return notify_fail("只有版本發佈站點才能修改表情動詞。\n");

        if (! arg || sscanf(arg, "%s %s", from, to) != 2)
                return help(me);

        emote = EMOTE_D->query_emote(from);
        if (! emote || ! sizeof(emote))
                return notify_fail("沒有(" + from + ")這個表情動詞。\n");

        if ((toemote = EMOTE_D->query_emote(to)) && sizeof(toemote))
                return notify_fail("表情動詞(" + to + ")已經存在，不能覆蓋。\n");

        toemote = allocate_mapping(sizeof(emote));
        ks = keys(emote);
        for (i = 0; i < sizeof(ks); i++)
                toemote[ks[i]] = emote[ks[i]];

        EMOTE_D->set_emote(to, toemote);
        printf("表情動詞(%s)複製到了(%s)。\n", from, to);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : cpemote <from> <to>

這個命令將原名為 <from> 的表情動詞複製成為名字為 <to> 的新表
情動詞。注意：原先必須不能存在名為 <to> 的表情動詞，該操作不
能覆蓋原先已經存在的表情動詞。

由於表情動詞會在版本同步時更新，因此只有版本發佈站點才能夠使
用這個命令。

see also：edemote、rnemote
HELP );
        return 1;
}