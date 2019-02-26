// workd.c

/********************************************************
  工作管理守護

絕代雙驕使用類似於 QUEST_D 的工作管理機制，所有的簡單工作
並不保存在請求或者執行具體工作的 npc 或者房間上，而是保存
在 /adm/daemons/work/ 目錄下以該工作英文命名的程序中， 比
如客棧工作即為 /adm/daemons/work/kezhan.c。這樣可以方便全
局的管理、修改和簡化調用(比如同類工作就不要複製一次代碼)。

系統(globals.h)提供的宏定義：

#define WORK_DIR     "/adm/daemons/work/"

WORK_D 提供的操作 API：

int    request_work(object who, object ob, string name);
string assign_work(object who, string name);
int    query_work(object who, string name);
int    start_work(object who, string name);
int    finish_work(object who, object ob, string name, mixed m);

WORK_OB 必須提供的接口：

int    request_work(object me, object ob);
int    query_work(object who);
string assign_work(object who);
int    start_work(object me);
int    finish_work(object me, object ob);

********************************************************/

#include <ansi.h>

#define WORK_DIR     "/adm/daemons/work/"

public int request_work(object who, object ob, string name)
{
        if (! playerp(who) || playerp(ob))
                return 0;

        if (! can_talk_with(ob, who))
                return 0;

        if (! file_size(WORK_DIR + name + ".c"))
                return 0;
                
        return (WORK_DIR + name + ".c")->request_work(who, ob);
}

public string assign_work(object who, string name)
{
        if (! playerp(who) || ! interactive(who))
                return 0;

        if (! file_size(WORK_DIR + name + ".c"))
                return 0;
                
        return (WORK_DIR + name + ".c")->assign_work(who);
}

public int query_work(object who, string name)
{
        if (! playerp(who) || ! interactive(who))
                return 0;

        if (! file_size(WORK_DIR + name + ".c"))
                return 0;
                
        return (WORK_DIR + name + ".c")->query_work(who);
}

public int start_work(object who, string name)
{
        if (! playerp(who) || ! interactive(who))
                return 0;

        if (! file_size(WORK_DIR + name + ".c"))
                return 0;
                
        return (WORK_DIR + name + ".c")->start_work(who);
}

public varargs int finish_work(object who, object ob, string name, mixed m)
{
        if (! playerp(who) || playerp(ob))
                return 0;

        if (! can_talk_with(ob, who))
                return 0;

        if (! file_size(WORK_DIR + name + ".c"))
                return 0;

        if (m)
                return (WORK_DIR + name + ".c")->finish_work(who, ob, m);
        else return (WORK_DIR + name + ".c")->finish_work(who, ob);
}

public string query_all_work()
{
        string *wlist;
        string info;
        string work;
        mixed *winfo;

        wlist = get_dir(WORK_DIR + "*.c");
        if (! arrayp(wlist) || ! sizeof(wlist))
                return "目前系統中沒有任何工作。\n";

        info = HIC "目前系統中有 " HIW + sizeof(wlist) + HIC " 項工作：\n" NOR
               HIW "─工作──獎勵───人數──最低經驗──最高經驗─\n" NOR;
        foreach(work in wlist)
        {
                winfo = (WORK_DIR + work + ".c")->query_info();
                info += sprintf(WHT "%-10s" CYN " %-10d %-10d %-10d %-10d\n" NOR,
                                winfo[0], winfo[1], winfo[2], winfo[3], winfo[4]);
        }
        info += HIW "─────────────────────────" NOR;
        return info;
}