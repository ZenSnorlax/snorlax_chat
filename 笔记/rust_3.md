## rust

## 错误处理

![](./picture/rust错误处理.png)

> 流程图 

```mermaid
graph TD
A(unwap\n expect)-->B(Box< dyn Error>\n anyhow::Error)
-->C(自定义错误类型\n 手动实现From/Error trait)
-->D(借助thiserror简化\n 自定义错误编写)
```
