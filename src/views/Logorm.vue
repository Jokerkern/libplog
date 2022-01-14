<template>
  <div class="Logorm">
    <SideMenu class="Logorm-left"></SideMenu>
    <div class="Logorm-right">
      <el-row
        ><el-form :inline="true" size="mini">
          <el-form-item>
            <el-date-picker
              v-model="value1"
              type="datetimerange"
              range-separator="至"
              start-placeholder="开始日期"
              end-placeholder="结束日期"
              value-format="timestamp"
            >
            </el-date-picker>
          </el-form-item>
          <el-form-item label="模块">
            <el-input v-model="logger" placeholder="请输入模块名"></el-input>
          </el-form-item>
          <el-form-item label="级别">
            <el-select v-model="level" placeholder="请选择级别" clearable>
              <el-option
                v-for="item in options"
                :key="item.value"
                :label="item.label"
                :value="item.value"
              >
              </el-option>
            </el-select>
          </el-form-item>
          <el-form-item style="width:6%">
            <el-select v-model="order">
              <el-option
                v-for="item in optionsOrder"
                :key="item.value"
                :label="item.label"
                :value="item.value"
              >
              </el-option>
            </el-select>
          </el-form-item>
          <el-form-item label="内容">
            <el-input v-model="input" placeholder="请输入搜索关键字"></el-input>
          </el-form-item>
          <el-form-item>
            <el-button @click="clickSearch" :disabled="isDisabled"
              >搜索</el-button
            >
          </el-form-item>
        </el-form>
      </el-row>
      <!-- <div id="app">
      {{message}}
      </div> -->
      <el-table
        :data="message"
        border
        :max-height="fullHeight"
        :header-cell-style="{ 'text-align': 'center' }"
        v-loading="loading"
      >
        <el-table-column
          prop="time"
          label="时间"
          width="300"
          align="center"
        ></el-table-column>
        <el-table-column
          prop="logger"
          label="模块"
          width="200"
          align="center"
        ></el-table-column
        ><el-table-column
          prop="level"
          label="级别"
          column-key="date"
          width="200"
          align="center"
          :filters="[
            { text: 'info', value: 'info' },
            { text: 'debug', value: 'debug' },
            { text: 'warning', value: 'warning' },
            { text: 'error', value: 'error' },
          ]"
          :filter-method="filterHandler"
        ></el-table-column>
        <el-table-column prop="log" label="内容" align="left">
          <template slot-scope="scope">
              <label v-html="sensitiveWords(scope.row.log)"></label>
            </template>
        </el-table-column>
      </el-table>
      <el-pagination
        @size-change="handleSizeChange"
        @current-change="handleCurrentChange"
        :current-page.sync="currentPage"
        :page-sizes="[5, 10, 20, 40]"
        :page-size="pagesize"
        layout="total, sizes, prev, pager, next, jumper"
        :total="total"
        :disabled="isDisabled"
        align="center"
      >
        //这是显示总共有多少数据
      </el-pagination>
    </div>
  </div>
</template>

<script>
import SideMenu from "./SideMenu.vue";
import { Query } from "@/request/user.js";
export default {
  name: "Logorm",
  components: {
    SideMenu,
  },

  data() {
    return {
      options: [
        {
          value: "info",
          label: "info",
        },
        {
          value: "debug",
          label: "debug",
        },
        {
          value: "warning",
          label: "warning",
        },
        {
          value: "error",
          label: "error",
        },
      ],
      optionsOrder: [
        {
          value: "asc",
          label: "正序",
        },
        {
          value: "desc",
          label: "倒序",
        },
      ],
      order: "asc",
      logger: "",
      input: "",
      level: "",
      message: [],
      currentPage: 1,
      pagesize: 10,
      total: 0,
      fullHeight: document.documentElement.clientHeight - 150,
      loading: false,
      id: 0,
      value1: null,
      isDisabled: false,
      
    };
  },
  methods: {
    sensitiveWords(value1) {
        let reg = new RegExp(this.input, "g");
        value1 = value1.replace(reg, '<font color="red">' + this.input + '</font>')
      
      return value1;
    },
    search() {
      this.loading = true;
      //var data = "/"+this.input;
      this.isDisabled = true;
      Query({
        id: this.id,
        beginTime: this.value1 ? this.value1[0] : 0,
        endTime: this.value1 ? this.value1[1] : 0,
        file: this.logger,
        level: this.level,
        log: this.input,
        order: this.order,
        pageSize: this.pagesize,
        pageNum: this.currentPage,
      }).then((res) => {
        //console.log(res.data);
        this.message = res.data.slice();
        this.total = res.total;
        this.loading = false;
        this.isDisabled = false;
        //console.log(this.message);
      });

      /*Query({log: this.input}).then((res) =>{
            console.log(res.data);
            this.message=[];
            this.message.push.apply(this.message,res.data);
            console.log(this.message);
        })*/
    },
    clickSearch() {
      //var data = "/"+this.input;
      this.loading = true;
      this.currentPage = 1;
      this.isDisabled = true;
      Query({
        beginTime: this.value1 ? this.value1[0] : 0,
        endTime: this.value1 ? this.value1[1] : 0,
        file: this.logger,
        level: this.level,
        log: this.input,
        order: this.order,
        pageSize: this.pagesize,
        pageNum: this.currentPage,
      }).then((res) => {
        //console.log(res.data);
        this.message = res.data.slice();
        this.total = res.total;
        this.loading = false;
        this.isDisabled = false;
        this.id = this.message.length != 0 ? this.message[0].ID : 0;
        //console.log(this.message);
      });
      /*Query({log: this.input}).then((res) =>{
            console.log(res.data);
            this.message=[];
            this.message.push.apply(this.message,res.data);
            console.log(this.message);
        })*/
    },
    filterHandler(value, row, column) {
      const property = column["property"];
      return row[property] === value;
    },
    handleSizeChange: function (size) {
      this.pagesize = size;
      this.search();
      //console.log(size); //每页下拉显示数据
    },
    handleCurrentChange: function (event) {
      this.currentPage = event;
      this.search();
    },
  },
};
</script>

<style lang="stylus" scoped>
.Logorm {
  display: flex;

  .Logorm-left {
    box-sizing: border-box;
  }

  .Logorm-right {
    box-sizing: border-box;
    width: calc(100% - 200px);
    padding: 8px 24px;
    flex: 1;
  }
}
</style>