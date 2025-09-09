import spacy
import networkx as nx
import matplotlib.pyplot as plt

# Load the spaCy English model
nlp = spacy.load("en_core_web_sm")

def analyze_sentence(sentence):
    """Analyze the grammatical structure of the sentence and build a dependency graph."""
    # Process the sentence with spaCy
    doc = nlp(sentence)
    
    # Create a directed graph
    G = nx.DiGraph()
    
    # Iterate over the tokens to identify dependencies
    for token in doc:
        # Add edges to the graph with the dependency label as edge attribute
        G.add_edge(token.head.text, token.text, label=token.dep_)
    
    return G

def display_dependency_graph(G, sentence):
    """Display the dependency graph using matplotlib and networkx."""
    pos = nx.spring_layout(G)  # Position the nodes using spring layout
    plt.figure(figsize=(12, 8))
    
    # Draw nodes and edges
    nx.draw(G, pos, with_labels=True, node_color="skyblue", node_size=2000, font_size=10, font_weight="bold", arrows=True)
    
    # Draw edge labels for dependency relationships
    edge_labels = nx.get_edge_attributes(G, 'label')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_color='red')
    
    plt.title(f"Dependency Graph for: '{sentence}'")
    plt.show()

# Input sentence
sentence = "The quick brown fox jumps over the lazy dog."

# Analyze the sentence to get the dependency graph
G = analyze_sentence(sentence)

# Display the dependency graph
display_dependency_graph(G, sentence)
