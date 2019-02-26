// medical-book.c

inherit ITEM;

#include <ansi.h>
#include <medical.h>

int is_book() { return 1; }

void setup()
{
        string msg;
        mapping med;
        string *ks;
        int i;

        if (clonep())
                return;

        msg = query("long");
        med = query("can_make");
        if (! mapp(med) || ! sizeof(med))
                return;

        ks = keys(med);
        msg += "上面記載了";
        for (i = 0; i < sizeof(ks); i++)
        {
                if (file_size(MEDICINE(ks[i]) + ".c") < 0)
                {
                        log_file("log", "No such medicine:" + MEDICINE(ks[i]) +
                                 "\n");
                        delete("can_make/" + ks[i]);
                        continue;
                }
                if (i) msg += "、";
                msg += MEDICINE(ks[i])->name();
        }
        msg += "的煉製方法，倒是可以仔細讀讀(read)，琢磨一下。\n";
        msg = sort_string(msg, 64);
        set("long", msg);
}

void init()
{
        add_action("do_read", "read");
}

int do_read(string arg)
{
        object me;
        mapping med;
        string skill;
        string m_name;
        string fm_name;
        string *ks;
        int lvl;
        int i;
        int jing_cost;

        if (! arg)
                return notify_fail("你要讀什麼？\n");

        if (sscanf(arg, "%s from %s", m_name, arg) != 2)
                return notify_fail("研究配製藥物：read 藥名 from " +
                                   query("id") + "\n");

        if (! id(arg))
                return notify_fail("沒有這本書啊。\n");

        med = query("can_make");
        if (! mapp(med) || ! sizeof(med))
        {
                write(name() + "上面並沒有記載任何值得"
                      "特別研究的內容。\n");
                return 1;
        }

        me = this_player();
        if (query("can_make/" + m_name, me))
        {
                write("你已經通曉了「" + m_name + "」的祕密，沒什麼好研究的了。\n");
                return 1;
        }

        ks = keys(med);
        for (i = 0; i < sizeof(ks); i++)
        {
                if (filter_color(MEDICINE(ks[i])->name()) == m_name)
                        break;
        }

        if (i >= sizeof(ks))
        {
                write(name() + "上面並沒有記載有關" +
                      m_name + "的內容。\n");
                return 1;
        }

        fm_name = "「" + MEDICINE(ks[i])->name() + "」";
        skill = query("skill/name");
        lvl = (int)me->query_skill(skill, 1);
        if (! lvl)
        {
                write("你現在對" + to_chinese(skill) + "還是"
                      "一竅不通，怎麼研究得明白？\n");
                return 1;
        }

        jing_cost = med[ks[i]] / 2 + 50;
        if (jing_cost > query("jing", me))
        {
                set("jing", 0, me);
                write("你覺得你現在精神不濟，難以研究有關" +
                      fm_name + "的知識。\n");
                return 1;
        }

        me->receive_damage("jing", jing_cost);

        if (lvl < (int)med[ks[i]])
        {
                write("你覺得" + fm_name + "實在是"
                      "太複雜了，以你目前的" + to_chinese(skill) +
                      "的學識恐怕還難以弄明白。\n");
                return 1;
        }

        if (random(lvl) < (int)med[ks[i]])
        {
                write(random(2) ? "你研究了一會兒有關" + fm_name +
                                  "的內容，有些收穫，不過還沒有徹底明白。\n"
                                : "你仔細閲讀了一會兒有關" + m_name +
                                  "的內容，明白了不少其中奧妙。\n");
                return 1;
        }

        write("你細細的研讀了有關" + fm_name +
              "的內容，終於恍然大悟，徹底明白了其中的奧妙。\n");
        write(HIC "你學會了煉製" + fm_name + HIC "的方法。\n");
        set("can_make/"+m_name, ks[i], me);
        return 1;
}