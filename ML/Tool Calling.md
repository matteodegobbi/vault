#nlp #ml #dl 

> [!summary] 
> Tool calling allows LLMs to use external resources like APIs, functions, databases, programming language interpreters, calculators, web search, etc. It allows LLMs to act in order to complete some tasks that are explicitly or implicitly required in the prompt.
> This allows LLM to do more than generate text and it's the first step towards using LLMs as agents.
# Tool use
To use tools we build a system with the following steps in mind:
1. Task understanding: the model interprets the user request (in the prompt) and determines whether it can answer directly or needs external help, this step is carried out by the LLM itself (usually [[Chain of Thought]] is used to improve this step). The decision to invoke a tool is carried out when the LLM samples a token that indicates a need for external assistance (e.g. `<tool_use>`)
2. Tool selection: the tool is chosen based on the task (e.g., web search for current info, calculator for math, code interpreter for data processing) in this step either the tool is chosen automatically by the LLM (e.g. `<tool_use:calculator>`) or with more advanced methods using a separate tool selection model (explain later in this note [[#Tool selection]])
3. Argument construction: the LLM formats inputs into a structured schema (often JSON or a predefined command format) to be passed to the actual tool e.g. `{"tool": "calculator","expression": "sqrt(847)*23"}`
4. Execution: the system (not the model itself) executes the tool call and returns the result.
5. Result integration: the LLM incorporates the tool output into a final response formatted in a proper way.

Steps 1, 3, 5 and possibly 2 are carried out by the LLM itself, we consider two possibilities for teaching a model how to use a tool:
1. Supervised Fine-Tuning: The model is directly fine-tuned on a dataset of prompt-tool-response sequences, learning how to know when to use a tool, how to select the appropriate tool, how to format the arguments and how to format the response. This requires a good quality dataset with annotated tools and examples of prompts that both require tools and prompts than don't.
2. Prompting: The usage of the tools is explained in some system prompt
![[Pasted image 20260325173847.png]]
![[Pasted image 20260325173904.png]]

In any case the provided code API or tools should provide some LLM facing documentation, necessary for the LLM to see how to call the tool but should not provide internal details about how the tool is implemented, basically a well documented black box.

If using method 2 via prompting we could use another powerful reasoning LLM that has been finetuned to write the description of APIs provided to it. Basically this avoids human work in having to describe to the LLM the API for any new tool and avoids having to finetune the model for tool use by using a different "tool description writer" LLM. 

Possible actions and tools are:
- Calculator
- Email / messages
- Code execution (in a sandboxed environment)
- Web search
- DB search
- Weather APIs, location etc.

- ---
# Tool selection
To try to solve the problem of having many tools (leading to needle in haystack sort of problems) some techniques have been developed to save context length and reduce the search space for tool selection to only candidate relevant ones.
Basically we can use various methods like [[Retrieval Augmented Generation]], external routers or other LLMs to select only a small list of candidate tools to present to the main LLM.
This reduces distraction problems and context length waste in the main LLM by offloading this pre-selection to an external system.
# Standardization: MCP
Model context protocol (MCP) is a way to connect external tools to LLM in a standard way. It was invented to avoid having to create the same tool multiple times for different LLMs.

It is structured as:
* MCP server, serving the various tools to be used by the LLMs
* MCP client, integrated into the LLM application, handles the communication with the MCP server.
For example:
![[Pasted image 20260327002358.png]]
