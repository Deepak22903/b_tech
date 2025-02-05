from dotenv import load_dotenv
import os
from mira_sdk import MiraClient, Flow

load_dotenv()

# Initialize the client
client = MiraClient(config={"API_KEY": os.getenv("MIRA_API_KEY")})

version = "1.0.3"
input_data = {
    "blog_topic": "How to invest in stocks",
    "content_type": "",
    "audience_requirements": ""
}

# If no version is provided, latest version is used by default
if version:
    flow_name = f"@super-labs/blog-post-generator/{version}"
else:
    flow_name = "@super-labs/blog-post-generator"

result = client.flow.execute(flow_name, input_data)
print(result)
