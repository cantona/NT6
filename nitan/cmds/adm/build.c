// build.c
// created by doing

#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        if (! SECURITY_D->valid_grant(me, "(admin)"))
        {
                write("你沒有權限編譯" + LOCAL_MUD_NAME() + "的版本。\n");
                return 1;
        }

        if (! arg)
                return notify_fail("指令格式: build <路徑名> | version | new | cancel\n");

        if (arg == "version")
                return VERSION_D->generate_version();

        if (arg == "cancel")
                return VERSION_D->build_cancel();

        if (arg == "new")
                return VERSION_D->build_new();

        if (arg[0] != '/')
                return notify_fail("你必須輸入一個完整的路徑名才可以。\n");

        return VERSION_D->build_path(arg);
}

int help (object me)
{
        write(@HELP
指令格式: build <路徑名> | version | cancel | new

編譯生成用於發佈的MUDLIB版本，如果輸入了路徑名，就更新當前版
本的某一個路徑。更新路徑名的方式將無條件覆蓋版本目錄下的文件。

build version 生成當前MUDLIB的最新發布版本。
build cancel  終止當前生成版本的操作，恢復以前的版本信息。
build /       強行從新覆蓋版本目錄下的所有文件。
build new     生成新的版本號。

注意，build cancel是一個破壞數據完整性的操作，因為這個操作本
身並不能恢復應該被覆蓋的版本。在使用了build cancel以後，建議
運行build / 以重新生成所有版本。

build new 則是配合build <路徑名>使用的，當分別更新了一些路徑
以後，有必要生成一個新的版本號，已備其他站點自動更新。

HELP );
        return 1;
}