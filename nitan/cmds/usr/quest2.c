// This program is a part of NT MudLIB
// quest1.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping q;
        string name, npc;

        if( query("ultra_count", me) )
                write(sprintf("南賢交給你的宗師任務，你已經連續完成了 %d 個。\n",
                              query("ultra_count", me)));

        if( !query("ultraquest/npc1", me) )
        {
                write("你現在沒有領任何任務！\n");
                return 1;
        }

        if( query("ultraquest/npc5", me) )
        {
                npc=query("ultraquest/npc5", me);
                name=query("ultraquest/name5", me);
        } else
        if( query("ultraquest/npc4", me) )
        {
                npc=query("ultraquest/npc4", me);
                name=query("ultraquest/name4", me);
        } else
        if( query("ultraquest/npc3", me) )
        {
                npc=query("ultraquest/npc3", me);
                name=query("ultraquest/name3", me);
        } else
        if( query("ultraquest/npc2", me) )
        {
                npc=query("ultraquest/npc2", me);
                name=query("ultraquest/name2", me);
        } else
        {
                npc=query("ultraquest/npc1", me);
                name=query("ultraquest/name1", me);
        }

        if( !mapp(q=query("ultraquest/quest", me)) )
        {
                if( query("ultraquest/id", me) )
                {
                        write("你現在的任務是去殺了幕後黑手"+query("ultraquest/name", me)+"("+
                              query("ultraquest/id", me)+")，提他的人頭給南賢。\n");
                        return 1;
                }
                write("你現在的任務是去尋找線索知情人" + name + "(" + npc + ")。\n" +
                      "聽説他前段日子在"+query("ultraquest/place", me)+"出現過。\n");
                return 1;
        } else
        {
                switch (q["type"])
                {
                case "kill":
                        write(name + "(" + npc + ")吩咐你去割下" HIR +
                              q["name"] + "(" + q["id"] + ")" + NOR "的人頭，回來交差。\n");
                        return 1;

                case "give":
                        write(name + "(" + npc + ")吩咐你去把包裹送到" HIR +
                              q["name"] + "(" + q["id"] + ")" + NOR "的手裏，回來交差。\n");
                        return 1;

                case "send":
                        write(name + "(" + npc + ")吩咐你去把信送到" HIR +
                              q["name"] + "(" + q["id"] + ")" + NOR "的手裏，回來交差。\n");
                        return 1;

                case "guard":
                        write(name + "(" + npc + ")吩咐你留在他那裏保護他。\n");
                        return 1;

                case "mathematics":
                        write(name + "(" + npc + ")吩咐你和他比試演算。\n");
                        return 1;

                case "literate":
                        write(name + "(" + npc + ")吩咐你和他比試詩詞。\n");
                        return 1;

                case "chess":
                        write(name + "(" + npc + ")吩咐你和他比試棋技。\n");
                        return 1;

                case "calligraphy":
                        write(name + "(" + npc + ")吩咐你幫他寫好書法。\n");
                        return 1;

                case "drawing":
                        write(name + "(" + npc + ")吩咐你幫他繪畫。\n");
                        return 1;

                case "medical":
                        write(name + "(" + npc + ")吩咐你幫他治病。\n");
                        return 1;
                }
        }

        write("你現在沒有領任何任務！\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : quest2 顯示出你當前的宗師任務。
HELP );
        return 1;
}

